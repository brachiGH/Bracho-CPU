<script setup>
import NumberedTextarea from './binaryViewer.vue';
import { ref } from 'vue';

const langueType = ref("b--");
</script>

<template>
  <div class="TextEditor">
    <div class="btn-group" role="group" aria-label="Horizontal radio toggle button group">
      <input type="radio" id="vbtn-radio1" class="btn-check" name="vbtn-radio" v-model="langueType" value="b--" autocomplete="off" checked>
      <label class="btn btn-primary" for="vbtn-radio1">B--</label>
      <input type="radio" id="vbtn-radio2" class="btn-check" name="vbtn-radio" v-model="langueType" value="assembly" autocomplete="off">
      <label class="btn btn-primary" for="vbtn-radio2">Assembly</label>
      <input type="radio" id="vbtn-radio3" class="btn-check" name="vbtn-radio" v-model="langueType" value="binary" autocomplete="off">
      <label class="btn btn-primary" for="vbtn-radio3">Binary</label>
    </div>
    {{ langueType }}

    
    <!-- Uncomment and modify these sections as needed
    <div class="form-floating">
      <textarea class="form-control" placeholder="Enter assembly code here." style="height: 600px; width: 500px;"></textarea>
      <label for="floatingTextarea2">Enter assembly code here.</label>
    </div>
    <div class="form-floating">
      <textarea class="form-control" placeholder="Enter b-- code here." style="height: 600px; width: 500px;"></textarea>
      <label for="floatingTextarea2">Enter b-- code here.</label>
    </div>
    -->
  </div>
</template>

<style scoped>
.TextEditor {
  font-size: 1.2rem;
}
</style>
