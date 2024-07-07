function replaceEvery11thSpaceWithNewline(text) {
  let spaceCount = 0;
  let newText = '';
  
  for (let i = 0; i < text.length; i++) {
    if (text[i] === ' ') {
      spaceCount++;
      if (spaceCount === 11) {
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