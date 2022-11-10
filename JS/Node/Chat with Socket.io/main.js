const express = require('express');
const app = express();
const server = require('http').createServer(app);
const { Server } = require("socket.io");
const io = new Server(server);

server.listen(3000, () => {
    console.log(`Example app listening on port 3000`)
})

app.get("/", (req, res) => {
    res.sendFile(__dirname + "/index.html")
})

users = []
connections = []

io.on("connection", (socket) => {
    console.log("Socket Connected");
    connections.push(socket)

    socket.on("disconnect", (data) => {
        console.log("Socket Disconnected");
        connections.splice(connections.indexOf(socket), 1)
    })

    socket.on("send msg", (data)=>{
        socket.broadcast.emit ("add msg" ,data)
    })
})

