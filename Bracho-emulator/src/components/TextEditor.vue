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
  </div>
</template>

<script>
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
    }
  },
  computed: {
    linesofcode() {
      return (code) => code.split('\n');
    },
  }
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
</style>





<!-- <template>
  <div class="numbered-textarea">
    <div class="line-numbers">
      <span v-for="(line, index) in lines" :key="index">{{ index + 1 }}</span>
    </div>
    <textarea :value="content" readonly></textarea>
  </div>
</template>

<script>
export default {
  name: 'NumberedTextarea',
  props: {
    content: {
      type: String,

    
        
          
    

        
        Expand All
    
    @@ -19,6 +43,9 @@ export default {
  
      required: true
    }
  },
  computed: {
    lines() {
      return this.content.split('\n');
    }
  }
}
</script>
<style scoped>
.numbered-textarea {
  display: flex;
  align-items: flex-start;
  font-family: monospace;
}
.line-numbers {
  text-align: right;
  padding-right: 10px;
  border-right: 1px solid #ccc;
  user-select: none;
}
.line-numbers span {
  display: block;
}
textarea {
  border: none;
  resize: none;
  outline: none;
  padding-left: 10px;
  width: 100%;
  height: 600px;
}
</style> -->