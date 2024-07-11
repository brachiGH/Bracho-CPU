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


function fillmemoryWithBanlk(code) {
  if (code.split(" ").length < 0xFFF) {
    code = code + Array(0xFFF - code.split(" ").length + 2).fill("0000").join(" ")
  }

  return code;
}

function numberToHex2Bytes(num) {
  if (num < 0) {
    num = num & 0xFFFF;
  }

  // Convert the number to a hexadecimal string
  let hexString = num.toString(16);
  
  // Pad the string with leading zeros if necessary to ensure it has a length of 4
  while (hexString.length < 4) {
    hexString = '0' + hexString;
  }
  
  return hexString;
}


function cleanCode(input) {
  // Split the input string into lines
  const lines = input.split('\n');
  
  // Process each line
  const processedLines = lines.map(line => line.trimStart()) // Remove leading spaces
    .filter(line => line !== '' && !line.startsWith('@') && !line.startsWith('#')); // Remove empty lines and lines starting with '@' or '#'
  
  // Join the remaining lines back into a single string
  return processedLines;
}