<script setup>
import '../js/utilites.js'
</script>


<template>
    <div class="grid-container">
        <div class="input-group mb-3">
            <span class="input-group-text">A</span>
            <input type="text" :value="registerList['A']" class="form-control" readonly>
        </div>

        <div class="input-group mb-3">
            <span class="input-group-text">B</span>
            <input type="text" :value="registerList['B']" class="form-control" readonly>
        </div>

        <div class="input-group mb-3">
            <span class="input-group-text">C</span>
            <input type="text" :value="registerList['C']" class="form-control" readonly>
        </div>

        <div class="input-group mb-3">
            <span class="input-group-text">PC</span>
            <input type="text" :value="registerList['PC']" class="form-control" readonly>
        </div>

        <div class="input-group mb-3">
            <span class="input-group-text">IR</span>
            <input type="text" :value="registerList['IR']" class="form-control" readonly>
        </div>

        <div class="input-group mb-3">
            <span class="input-group-text">LR</span>
            <input type="text" :value="registerList['LR']" class="form-control" readonly>
        </div>

        <div class="input-group mb-3">
            <span class="input-group-text">Flags</span>
            <input type="text" :value="JSON.stringify(registerList['flags'])" class="form-control" readonly>
        </div>

    </div>
</template>
  
<script>
  export default {
    name: 'registerBank',
    props: {
      registerList: {
        type: Object,
        required: true
      }
    },
  };
</script>
  
<style scoped>
  span {
    width: 110px;
    align-content: center;
    justify-content: center;
  }

  .grid-container {
    font-family: monospace;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
  }
</style>
  