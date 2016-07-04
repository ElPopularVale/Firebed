#Firebed

Sychronized IoT architecture. It is similar to Firebase but for embedded constrained devices. The idea is that all devices will be synchronized to a central database in real time (no REST) so that one change in the mobile app or web browser is reflected in all devices including embedded edge ones immediately.

###HOW IT WORKS
A device with CoAP and DTLS support makes a WebSocket handshake over CoAP more or less like this:
```
GET /.well-known/coap CoAP
Host: example.org
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==
Sec-WebSocket-Protocol: firebed
Sec-WebSocket-Version: 13

CoAP 101 Switching Protocols
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo=
Sec-WebSocket-Protocol: firebed
```
WebSockets was initially designed to work on browsers and servers but not on embedded devices. It can be implemented but it would consume so much bandwidth that would drain the battery of such device so that's why new protocols have been invented that are less "heavy". For example, Constrained Application Protocol CoAP works over UDP and uses less bytes to implement a REST interface. WebSockets however works over TCP so out work was focused in implementing it over UDP. However, since CoAP is REST the handshake can be done similarly and the WebSocket connection can be established. From there it would work normally using standard WebSocket messages.

The problem is that it can't be connected to browsers directly without an extension, so it is designed to work between devices and cloud servers. Now the cloud server could translate the coap websocket message to normal websockets in order to synchronize with the browser. The cloud server also keeps track of a MongoDB database that stores and updates values according to received data.