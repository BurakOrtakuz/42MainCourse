const express = require('express');
const WEB_SOCKET = require('ws');
const app = express();
const SERVER_SOCKET = require('http').createServer(app);
const server = new WEB_SOCKET.Server({server: SERVER_SOCKET});

app.use(express.static('PUBLIC'));
app.use(express.json());

app.get('/', (REQUEST, RESOURCE) => // HOME PAGE
	{
		RESOURCE.sendFile(__dirname + '/PUBLIC/INDEX.html');
	}
);

app.post('/AJAX/LOGIN', (REQUEST, RESOURCE) =>
	{
		console.log(REQUEST.body);
		RESOURCE.send({SUCCESS: true});
	}
);

server.on('connection', (SERVER_WEB_SOCKET, DEVICE) =>
	{
		SERVER_WEB_SOCKET.on('message', (SIGNAL) =>
			{
				const DATA = JSON.parse(SIGNAL.toString());
				console.log(DATA.SIGNAL_TYPE);
				console.log(DATA.PASSWORD);
			}
		);
	}
);

// Start the Express server.
SERVER_SOCKET.listen(3000, () => {
	console.log(`Listening at http://localhost:3000`);
});
