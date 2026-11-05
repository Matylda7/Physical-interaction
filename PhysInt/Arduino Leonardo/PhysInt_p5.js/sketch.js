let colors = [
  [0, 0, 0],     // 0: Black
  [255, 0, 0],   // 1: Red
  [0, 255, 0],   // 2: Green
  [0, 0, 255],   // 3: Blue
  [255, 255, 0], // 4: Yellow
  [0, 255, 255], // 5: Cyan
  [255, 0, 255], // 6: Magenta
];

let colorIndex = 0;
let isEraser = false;

let brushSize = 20;
let eraserSize = 24;

let port;
let connectBtn;
let reader;
let lineBuffer = "";

function setup() {
  createCanvas(800, 800);
  background(220);

  connectBtn = createButton('Connect Arduino Serial');
  connectBtn.position(150, 22);
  connectBtn.mousePressed(connectSerial);
}

function draw() {
  //bar background
  fill(240, 240, 240, 240);
  stroke(200);
  strokeWeight(1);
  rect(10, 10, 330, 45, 6);

  // color square
  fill(colors[colorIndex]);
  stroke(0);
  strokeWeight(1);
  rect(20, 18, 30, 30, 4);

  if (isEraser) {
    fill(150, 0, 0);
    stroke(0);
    text("ERASER", 70, 38);
  } else {
    fill(0, 150, 0);
    stroke(0);
    text("DRAWING", 70, 38);
  }
  fill(0); 

  //Drawing Logic
  if (isEraser) {
    stroke(220);       
    strokeWeight(eraserSize); 
    line(pmouseX, pmouseY, mouseX, mouseY);
  } else if (mouseIsPressed) {
    stroke(colors[colorIndex]);
    strokeWeight(brushSize);         
    line(pmouseX, pmouseY, mouseX, mouseY);
  }
}

async function connectSerial() {
  try {
    //opens selection pop-up, and opens the connection at 9600 baud rate
    port = await navigator.serial.requestPort();
    await port.open({ baudRate: 9600 });
    connectBtn.html('Connected');
    connectBtn.style('background-color', 'lightgreen');
    
    readSerialStream();
  } catch (err) {
    console.error('Serial connection failed:', err);
  }
}

async function readSerialStream() {
  try {
    //translates incoming binary data from USB port into text strings
    const textDecoder = new TextDecoderStream();
    port.readable.pipeTo(textDecoder.writable);
    reader = textDecoder.readable.getReader();

    //collects text datainto 
    async function readChunk() {
      const { value, done } = await reader.read();
      if (done) return;
      
      if (value) {
        lineBuffer += value;
        let lines = lineBuffer.split("\n");
        lineBuffer = lines.pop(); 

        for (let lineStr of lines) {
          let trimmed = lineStr.trim();
          if (trimmed.length > 0) {
            let val = int(trimmed);

            if (!isNaN(val) && val >= 0 && val < colors.length) {
              colorIndex = val;
              isEraser = false; 
            }
          }
        }
      }
      readChunk(); 
    }

    readChunk();
  } catch (error) {
    console.error('Read error:', error);
  }
}

function keyPressed() {
  if (key === 'e' || key === 'E') {
    isEraser = true;
  }
}

function keyReleased() {
  if (key === 'e' || key === 'E') {
    isEraser = false;
  }
}