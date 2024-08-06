const express = require('express');
const http = require('http');
const socketIo = require('socket.io');
const fetch = require('node-fetch');
const cors = require('cors');
const admin = require('firebase-admin');
const serviceAccount = require('./public/serviceAccountKey.json');

const app = express();
const server = http.createServer(app);
const io = socketIo(server);

admin.initializeApp({
    credential: admin.credential.cert(serviceAccount),
    databaseURL: 'https://iot-finalproject-60440-default-rtdb.firebaseio.com'
  });
 

app.use(cors());
app.use(express.static('public'));

// Socket.io connection handler
io.on('connection', (socket) => {
    console.log('A user connected');
    socket.on('disconnect', () => {
        console.log('User disconnected');
    });
});

// Endpoint to get washer logs
app.get('/washerLogs', async (req, res) => {
    let url = 'https://api.sheety.co/da2a5719d2e86338f90b61791524cc2b/ioTFinalProject/logWasher01';
    try {
        const response = await fetch(url);
        const json = await response.json();
        res.json(json.logWasher01S);
        
    } catch (error) {
        console.error('Error fetching washer logs:', error);
        res.status(500).send('Internal Server Error');
    }
    
});

// Endpoint to get dryer logs
app.get('/dryerLogs', async (req, res) => {
    let url = 'https://api.sheety.co/da2a5719d2e86338f90b61791524cc2b/ioTFinalProject/logDryer01';
    try {
        const response = await fetch(url);
        const json = await response.json();
        res.json(json.logDryer01S);
    } catch (error) {
        console.error('Error fetching dryer logs:', error);
        res.status(500).send('Internal Server Error');
    }
});

app.get('/washerLogs02', async (req, res) => {
    let url = 'https://api.sheety.co/da2a5719d2e86338f90b61791524cc2b/ioTFinalProject/logWasher02';
    try {
        const response = await fetch(url);
        const json = await response.json();
        res.json(logWasher02S);
    } catch (error) {
        console.error('Error fetching dryer logs:', error);
        res.status(500).send('Internal Server Error');
    }
});

app.get('/dryerLogs02', async (req, res) => {
    let url = 'https://api.sheety.co/da2a5719d2e86338f90b61791524cc2b/ioTFinalProject/logDryer02';
    try {
        const response = await fetch(url);
        const json = await response.json();
        res.json(json.logDryer02S);
    } catch (error) {
        console.error('Error fetching dryer logs:', error);
        res.status(500).send('Internal Server Error');
    }
});

async function getFirebaseData() {
    const database = admin.database();
    const ref = database.ref('/Data');
  
    ref.once('value', (snapshot) => {
      const data = snapshot.val();
      console.log('Firebase Data:', data);
    }, (error) => {
      console.error('Error fetching data:', error);
    });
  }
  app.get('/firebaseData', async (req, res) => {
    try {
      const db = admin.database();
      const ref = db.ref('/Data');
  
      ref.once('value', (snapshot) => {
        const data = snapshot.val();
        res.json(data);
      }, (error) => {
        console.error('Error fetching data:', error);
        res.status(500).send('Internal Server Error');
      });
    } catch (error) {
      console.error('Error:', error);
      res.status(500).send('Internal Server Error');
    }
  });
  
  
  // เรียกฟังก์ชั่นเพื่อดึงข้อมูล
  getFirebaseData();

// Start server
const PORT = process.env.PORT || 3000;
server.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});
