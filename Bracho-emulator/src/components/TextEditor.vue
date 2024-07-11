<script setup>
import { ref } from 'vue';
import { flag_asm } from '@/js/flagtest.js';


const langueType = ref("assembly");
const assemblycode = ref(flag_asm);
const bcode = ref("");
</script>

<template>
  <div class="TextEditor" style="width: 100%;">
    <div class="border-bottom border-light p-1" style="background-color: #393E46;">
      <div class="btn-group" role="group" aria-label="Horizontal radio toggle button group">
        <input type="radio" id="vbtn-radio1" class="btn-check" name="vbtn-radio" v-model="langueType" value="b--" autocomplete="off" checked>
        <label class="btn btn-light" for="vbtn-radio1">B--</label>
        <input type="radio" id="vbtn-radio2" class="btn-check" name="vbtn-radio" v-model="langueType" value="assembly" autocomplete="off">
        <label class="btn btn-light" for="vbtn-radio2">Assembly</label>
        <input type="radio" id="vbtn-radio3" class="btn-check" name="vbtn-radio" v-model="langueType" value="assemblyInstructions" autocomplete="off">
        <label class="btn btn-light" for="vbtn-radio3">Instructions</label>
      </div>
      
      <button  v-if="langueType === 'assembly'" onclick="callAssembler()" type="submit" class="btn btn-primary" style="float: right;">Assemble</button>
      <button  v-else-if="langueType === 'b--'" type="submit" class="btn btn-primary" style="float: right;">Compile</button>
    </div>

    <div v-if="langueType === 'assembly'" class="form-floating numbered-textarea m-1">
      <div class="line-numbers" ref="line-numbers-dom" @scroll="syncScroll('line-numbers-dom')">
        <span style="height: 5px;"></span>
        <span v-for="(line, index) in linesofcode(assemblycode)" :key="index">
          {{ index + 1 }}
        </span>
      </div>
      <textarea class="object-fit-scale textinput" placeholder="Enter assembly code."
              id="input-assemblycode" v-model="assemblycode"
              ref="assembly-editor-dom" @scroll="syncScroll('assembly-editor-dom')">
      </textarea>
    </div>

    <div v-else-if="langueType === 'b--'" class="form-floating numbered-textarea m-1">
      <div class="line-numbers" ref="line-numbers-dom" @scroll="syncScroll('line-numbers-dom')">
        <span style="height: 5px;"></span>
        <span v-for="(line, index) in linesofcode(bcode)" :key="index">
          {{ index + 1 }}
        </span>
      </div>
      <textarea class="object-fit-scale textinput" placeholder="Enter b-- code." v-model="bcode"
              ref="assembly-editor-dom" @scroll="syncScroll('assembly-editor-dom')">
      </textarea>
    </div>

    <div v-else-if="langueType === 'assemblyInstructions'" class="form-floating numbered-textarea m-1">
      <div class="line-numbers" ref="line-numbers-dom" style="border: none; text-align: left;">
        <span style="height: 5px;"></span>
        <span v-for="(line, index) in assemblyCodeLines" :key="index" :class="{ 'highlightCell': ((PCregister - 1) == (index+1)) }"
                        :id="'Instruction' + index">
          [{{ index + 1 }}]: {{ line }}
        </span>
      </div>
    </div>
  </div>
</template>

<script>
import '../js/utilites.js';


export default {
  name: 'TextEditor',
  methods: {
    syncScroll(origin) {
      if (this.isSyncing) return;
      this.isSyncing = true;
      
      const other = origin === 'line-numbers-dom' ? 'assembly-editor-dom' : 'line-numbers-dom';
      const originEl = this.$refs[origin];
      const otherEl = this.$refs[other];
      
      otherEl.scrollTop = originEl.scrollTop;
      otherEl.scrollLeft = originEl.scrollLeft;
      
      this.isSyncing = false;
    },
    Test() {
      return window.Bracho_program.cpu.PC;
    }
  },
  props: {
    assemblyCodeLines: {
      type: Array,
      required: true
    },
    PCregister: {
      type: Number,
      required: true
    },
  },
  computed: {
    linesofcode() {
      return (code) => code.split('\n');
    },
  },
}
</script>

<style scoped>
  .TextEditor {
    font-size: 1.2rem;
  }

  .line-numbers {
    text-align: right;
    padding-right: 10px;
    border-right: 1px solid #ccc;
    user-select: none;
    height: 600px;
    overflow: scroll;
    -ms-overflow-style: none;  /* Internet Explorer 10+ */
    scrollbar-width: none;  /* Firefox */
  }

  .line-numbers span {
    display: block;
    font-size: 1rem;
  }

  .numbered-textarea {
    display: flex;
    align-items: flex-start;
    font-family: monospace;
  }

  .textinput {
    width: 100%;
    height: 600px;
    font-size: 1rem;
    resize: none;
  }

  .btn-check:checked + .btn {
    background-color: #a0a1a2;
  }
</style>
