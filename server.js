var express = require("express");
var fs = require("fs");

// express démarre le serveur
var app = express();
const PORT = 8888;

app.use(express.static('public'));

app.listen(PORT, () => {
    console.log(`Server running at http://localhost:${PORT}`);
});
