<!-- src/components/FixedSections.vue -->
<template>
    <div class="container">
        <div class="section">
        <slot name="section1"></slot>
        </div>
        <div class="section">
        <slot name="section2"></slot>
        </div>
        <div class="section">
        <slot name="section3"></slot>
        </div>
    </div>
</template>
  
  <script>
  export default {
    name: 'FixedSections',
  };
  </script>
  
  <style scoped>
  .container {
    display: flex;
    width: 100vw;
    height: 100vh;
    overflow: hidden;
  }
  .section {
    flex: 1;
    display: flex;
    align-items: center;
    justify-content: center;
    border-left: 1px solid #ccc;
  }
  </style>
  