<template>
    <div class="grid-container">
      <div v-for="(row, rowIndex) in display" :key="rowIndex" class="grid-row">
        <div
          v-for="(cell, cellIndex) in row"
          :key="cellIndex"
          class="grid-cell"
          :style="{ backgroundColor: getColor(cell) }"
        ></div>
      </div>
    </div>
  </template>
  
  <script>
import { display } from '@/js/Bracho-CPU-core';

  export default {
    name: 'DisplayGrid',
    props: {
      display: {
        type: Array,
        required: true
      }
    },
    methods: {
      getColor(code) {
        const colors = {
          0: 'black',
          1: 'red',
          2: 'green',
          3: 'yellow',
          4: 'blue',
          5: 'magenta',
          6: 'cyan',
          7: 'white',
          8: 'grey', // Bright Black
          9: 'lightcoral', // Bright Red
          10: 'lightgreen', // Bright Green
          11: 'lightyellow', // Bright Yellow
          12: 'lightblue', // Bright Blue
          13: 'violet', // Bright Magenta
          14: 'lightcyan', // Bright Cyan
          15: 'whitesmoke' // Bright White
        };
        return colors[code] || 'black';
      }
    }
  };
  </script>
  
  <style scoped>
  .grid-container {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
  }
  
  .grid-row {
    display: flex;
  }
  
  .grid-cell {
    width: 5px; /* Adjust size as needed */
    height: 5px; /* Adjust size as needed */
  }
  </style>
  