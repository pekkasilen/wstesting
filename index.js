const fs = require("fs");
const knexConfig = require("./knexfile");
const knex = require("knex")(knexConfig["development"]);
const http = require('http');
const ws = require('ws')
const wss = new ws.Server({ noServer: true});

const accept = (req,res) => {
    console.log("connecting?")
    if(req.headers.upgrade.toLowerCase() != 'websocket'){
        res.end();
        return;
    }

    if (!req.headers.connection.match(/\bupgrade\b/i)) {
        res.end();
        return;
    }
    wss.handleUpgrade(req, req.socket, Buffer.alloc(0), onConnect);
}

const onConnect = (ws) => {
    console.log("onConnect")
    ws.on('message', (message)=> {
        console.log('' + message)
        
        ws.send(`Hello, ${message}, nice to see ya`)
    })
}

http.createServer(accept).listen(8080);











//const ffmpeg = require('ffmpeg');
/*Stream = require('node-rtsp-stream');
stream = new Stream({
    name: 'name',
    streamUrl: 'rtsp://admin:KauraKoira69@80.186.159.32:554',
    wsPort: 9999,
    ffmpegOptions: {
        '-stats': '',
        '-r':30
    }
})*/
