const express = require('express');
const app = express();
const cors = require('cors')

let db = {}

app.use(cors())

app.use(express.json({}));
app.use((err, req, res, next) => {
    if (err instanceof SyntaxError && err.status === 400 && 'body' in err) {
        console.error(err);
        return res.status(400).json({ status: 400, message: 'Invalid json' }); // Bad request
    }
    next();
});

const hasParam = (req, res, next) => {
    if (!req.params.id) res.status(400).json({error: 400, message: "Please inform the ID (i.e. /store/<id>)"})
    else next();
}

const existsInDB = (req, res, next) => {
    if (!db[req.params.id]) return res.status(404).send();
    else next();
}

app.get('/store/:id', hasParam, existsInDB, (req, res) => {
    res.json(db[req.params.id]);
});

app.put('/store/:id', hasParam, (req, res) => {
    if (req.headers['content-type'] !== 'application/json') return res.status(400).json({error: 400, message: 'Content Type must be json'});
    
    db[req.params.id] = req.body;
    res.status(200).json({status: 200, message: "OK"});
});

app.delete('/store/:id', hasParam, existsInDB, (req, res) => {
    delete db[req.params.id];
    res.status(200).json({status: 200, message: "OK"});
});

//http://localhost:3000/test.html
app.use('/',express.static(__dirname + '/html'));

app.listen(3000, 'localhost', ()=>{
    console.log('Started Server on localhost:3000');
});