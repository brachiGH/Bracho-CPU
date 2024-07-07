<template>
  <div class="numbered-textarea m-1">
    <div class="line-numbers" ref="line-numbers-dom" @scroll="syncScroll('line-numbers-dom')">
      <span v-for="(line, index) in lines" :key="index">{{ index + 1 }}</span>
    </div>
    <div  class="binary-viwer" ref="binary-viwer-dom" @scroll="syncScroll('binary-viwer-dom')">
      <div v-for="(line, index) in lines" :key="index">
        <span class="m-1" v-for="(word, wordindex) in words(line)" :id="wordindex+(11*index)">{{ word }}</span>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'NumberedTextarea',
  data() {
    return {
      isSyncing: false,
    };
  },
  methods: {
    syncScroll(origin) {
      if (this.isSyncing) return;
      this.isSyncing = true;
      
      const other = origin === 'line-numbers-dom' ? 'binary-viwer-dom' : 'line-numbers-dom';
      const originEl = this.$refs[origin];
      const otherEl = this.$refs[other];
      
      otherEl.scrollTop = originEl.scrollTop;
      otherEl.scrollLeft = originEl.scrollLeft;
      
      this.isSyncing = false;
    }
  },
  props: {
    content: {
      type: String,
      required: true
    }
  },
  computed: {
    lines() {
      return this.content.split('\n');
    },
    words() {
      return (line) => line.split(' ');
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
  height: 600px;
  overflow: scroll;
  -ms-overflow-style: none;  /* Internet Explorer 10+ */
  scrollbar-width: none;  /* Firefox */
}
.line-numbers::-webkit-scrollbar { 
    display: none;  /* Safari and Chrome */
}

.line-numbers span {
  display: block;
}

.binary-viwer {
  border: none;
  resize: none;
  outline: none;
  padding-left: 10px;
  height: 600px;
  width: 500px;
  background-color: #2b2a33;
  overflow: scroll;
}
</style>
