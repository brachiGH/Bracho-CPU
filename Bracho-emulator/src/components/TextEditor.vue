<script setup>
import { ref } from 'vue';


const langueType = ref("b--");
const assemblycode = ref("");
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
      </div>
      
      <button  v-if="langueType === 'assembly'" onclick="callAssembler()" type="submit" class="btn btn-primary" style="float: right;">Assemble</button>
      <button  v-else-if="langueType === 'b--'" type="submit" class="btn btn-primary" style="float: right;">Compile</button>
    </div>

    <div v-if="langueType === 'assembly'" class="form-floating m-1">
      <textarea class="form-control object-fit-scale" placeholder="Enter assembly code." id="input-assemblycode" v-model="assemblycode" style="height: 600px;"></textarea>
      <label for="floatingTextarea2">Enter assembly code.</label>
    </div>

    <div v-else-if="langueType === 'b--'" class="form-floating m-1">
      <textarea class="form-control object-fit-scale" placeholder="Enter b-- code." v-model="bcode" style="height: 600px;"></textarea>
      <label for="floatingTextarea2">Enter b-- code.</label>
    </div>
  </div>
</template>

<style scoped>
  .TextEditor {
    font-size: 1.2rem;
  }
</style>
