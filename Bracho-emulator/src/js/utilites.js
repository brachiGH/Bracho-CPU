function addNewlineEveryNthWord(text, n) {
  let spaceCount = 0;
  let newText = '';
  
  for (let i = 0; i < text.length; i++) {
    if (text[i] === ' ') {
      spaceCount++;
      if (spaceCount === n) {
        newText += '\n';
        spaceCount = 0;  // Reset the count after every 12th space
      } else {
        newText += text[i];
      }
    } else {
      newText += text[i];
    }
  }
  
  return newText;
}


function getCurrentTime() {
  const now = new Date();
  const hours = String(now.getHours()).padStart(2, '0');
  const minutes = String(now.getMinutes()).padStart(2, '0');
  const seconds = String(now.getSeconds()).padStart(2, '0');
  
  return `[${hours}:${minutes}:${seconds}]`;
}