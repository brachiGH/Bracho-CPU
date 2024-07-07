<script setup>
import { ref } from 'vue';
import 'bootstrap/dist/css/bootstrap.min.css';
import 'bootstrap/dist/js/bootstrap.bundle.min.js';

import assemblyTextEditor from './components/TextEditor.vue';
import NumberedTextarea from './components/binaryViewer.vue';
import FixedSections from './components/FixedSections.vue';



const textContent = ref("0000")

// Method to update textContent
const updateTextContent = (newContent) => {
  textContent.value = newContent;
};

// Expose the update method to the window object
window.updateTextContent = updateTextContent;

</script>

<template>
  <div id="app">
    <FixedSections class="modal-fullscreen m-0 p-0">
      <template #section1>
        <assemblyTextEditor />
      </template>
      <template #section2>
        <NumberedTextarea :content="textContent" />
      </template>
      <template #section3>
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
    },
  }
</script>

<style>

#app {
  width: 100%;
  height: 100%;
  padding: 0 0;
  margin: 0 0;
}
</style>
