<template>
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
</style>
