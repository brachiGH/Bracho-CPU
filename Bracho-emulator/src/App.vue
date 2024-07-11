<script setup>
import { ref } from 'vue';
import 'bootstrap/dist/css/bootstrap.min.css';
import 'bootstrap/dist/js/bootstrap.bundle.min.js';
import { controlUnite, registers, display, PCregister } from './js/Bracho-CPU-core.js'
import './js/utilites.js'


import TextEditor from './components/TextEditor.vue';
import NumberedTextarea from './components/binaryViewer.vue';
import FixedSections from './components/FixedSections.vue';
import console from './components/console.vue';
import DisplayGrid from './components/DisplayGrid.vue';
import registerBank from './components/registers.vue';

import { logMessages } from './components/console.vue';


const textContent = ref("0000");
const assemblyCodeLines = ref([]);

// Method to update textContent
const updateBinaryViewerContent = (newContent) => {

  textContent.value = addNewlineEveryNthWord(newContent, 10);
};

const clock = 1;
let Bracho_program = new controlUnite(clock);
// Expose the update method to the window object
window.Bracho_program = Bracho_program;

const executeBinaryInstructions = (content, assemblyCodeUnclean) => {
  assemblyCodeLines.value = cleanCode(assemblyCodeUnclean);

  updateBinaryViewerContent(content);

  Bracho_program.reset();
  let instructions = content.split(" ");
  Bracho_program.load(instructions);
}

// Expose the update method to the window object
window.executeBinaryInstructions = executeBinaryInstructions;

</script>

<template>
  <div id="app">
    <FixedSections class="modal-fullscreen m-0 p-0">
      <template #section1>
        <TextEditor :PCregister="PCregister" :assemblyCodeLines="assemblyCodeLines" />
        <console />
      </template>
      <template #section2>
        <div class="border-bottom border-light p-1" style="background-color: #393E46;position: absolute;">
          <div class="btn-group" role="group">
            <input class="btn btn-primary" type="button" @click="StartCPU" value="Start">
            <input class="btn btn-primary" type="button" @click="StepCPU" value="Step">
            <input class="btn btn-primary" type="button" @click="ResumeCPU" value="Resume">
            <input class="btn btn-primary" type="button" @click="PauseCPU" value="Pause">
            <input class="btn btn-primary" type="button" @click="StopCPU" value="Stop">
            <input class="btn btn-primary" type="button" @click="ResetCPU" value="Reset">
            <div class="btn-group">
              <button type="button" class="btn btn-warning dropdown-toggle" data-bs-toggle="dropdown" aria-expanded="false">
                Clock
              </button>
              <ul class="dropdown-menu clocklist">
                <span ref="showclock">Clock set to: {{ 1 }}</span>
                <li v-for="i in 4"><a class="dropdown-item" @click="changeClock(2**(-i))">{{ 2**(-i) }} Hz</a></li>
                <li v-for="i in 11"><a class="dropdown-item" @click="changeClock(2**(i-1))">{{ 2**(i-1) }} Hz</a></li>
                <li v-for="i in 11"><a class="dropdown-item" @click="changeClock((2**(i-1))*1000)">{{ 2**(i-1) }} HKz</a></li>
                <li v-for="i in 11"><a class="dropdown-item" @click="changeClock((2**(i-1))*1000000)">{{ 2**(i-1) }} HMz</a></li>
                <li><a class="dropdown-item" @click="changeClock(0)">As fast as my cpu can handle</a></li>
              </ul>
            </div>

          </div>
        </div>

        <NumberedTextarea :content="textContent" :PCregister="PCregister" style="padding-top: 50px;"/>


        <!-- <div v-for="(line, index) in assemblyCodeLines">
          <div :class="{ 'highlightCell': ((PCregister - 1) == (index+1))}">{{ line }}</div>
        </div> -->

      </template>
      <template #section3>
        <!-- {{ JSON.stringify(registers) }} -->
        <DisplayGrid :display="display" />

        <registerBank :registerList="registers"/>
      </template>
    </FixedSections>
  </div>
</template>

<script>
  export default {
    name: 'App',
    components: {
      NumberedTextarea,
      FixedSections,
      DisplayGrid,
      registerBank,
    },
    methods: {
      PauseCPU() {
        window.Bracho_program.pause();
      },
      StartCPU() {
        window.Bracho_program.isPaused = false;
        window.Bracho_program.shouldStop = false;
        window.Bracho_program.start();
      },
      ResumeCPU() {
        window.Bracho_program.resume();
      },
      StepCPU() {
        window.Bracho_program.executeAnInstruction();
      },
      StopCPU() {
        window.Bracho_program.stop();
      },
      ResetCPU() {
        window.Bracho_program.reset();
      },
      changeClock(i) {
        Bracho_program.SetClock(i);
        this.$refs["showclock"].innerText = "Clock set to: " + i;
      }
    },
  }

  window.logMessages = logMessages;
</script>

<style>

.clocklist {
  cursor: pointer;
  overflow: scroll;
  height: 400px;
}

#app {
  width: 100%;
  height: 100%;
  padding: 0 0;
  margin: 0 0;
}
</style>
