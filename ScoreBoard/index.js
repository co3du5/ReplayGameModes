const express = require('express');
const app = express();
var expressWs = require('express-ws')(app);
const path = require('path');
const WebSocket = require('ws');
const port = 8080;

var scores = {
    "team1":0,
    "team2":0}

var clients = new Set();

app.use(express.json())


app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'index.html'));
  });
  app.get('/admin', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'admin.html'));
  });

app.post('/modifyScore', (req, res) => {
    // console.log("Hello there")
    console.log(req.body)
    scores[req.body.team] += Number(req.body.value)
    // scores.team1 += 1;
    // scores.team2 += 1;
    
    broadcastUpdate(scores)
    res.send(scores);
});

app.get('/reset', (req, res) => {
    scores = {"team1":0,"team2":0}
    broadcastUpdate(scores)
    res.send(scores);
});

app.get('/getValues', (req, res) => {
    res.send(scores);
});

function broadcastUpdate(data) {
    const message = JSON.stringify(data);
    clients.forEach((client) => {
      if (client.readyState === WebSocket.OPEN) {
        client.send(message);
      }
    });
  }

app.ws('/getValues', function(ws, req) {
    clients.add(ws)
    ws.on('message', function(msg) {
      ws.send(JSON.stringify(scores));
    });
    ws.on('close', function(wsc) {
        clients.delete(wsc)
    })
  });

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}/`);
});