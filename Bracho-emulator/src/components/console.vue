<script setup>
import { ref } from 'vue';
import 'bootstrap/dist/css/bootstrap.min.css';
import 'bootstrap/dist/js/bootstrap.bundle.min.js';

</script>

<template>
    <div class="m-0 alert alert-dark" role="alert">console</div>
  <div class="console" style="width: 100%;" ref="console">
    <table class=" table rounded border">

         <!-- :class="{'table-danger' : (level == 'err'), 'table-secondary': (level == 'log')}" -->
        <row class="object-fit-scale" style="display: contents;" v-for="{level, message, time} in logMessages">
          <tr :class="{'table-danger' : (level == 'err'), 'table-secondary': (level == 'log')}">
              <td class='time-cell'>{{ time }}</td>
              <td>{{ message }}</td>
          </tr>
        </row>
    </table>
  </div>
</template>

<script>
export const logMessages = ref([]);
export default {
  name: 'console',
  methods: {
    scrollToElement() {
      const el = this.$refs["console"];

      if (el) {
        // Use el.scrollIntoView() to instantly scroll to the element
        el.scrollTo(0, el.scrollHeight);;
      }
    }
  },
  updated() {
    this.scrollToElement();
  }
}
</script>

<style scoped>
  .console {
    font-size: 0.8rem;
    display: block;
    overflow: scroll;
    height: 200px;
    width: 100%;
    font-family: monospace;
  }

  .time-cell {
    width: 10px;
  }

  .log-level-cell {
    width: 10px;
  }
</style>

