const express = require('express');
const app = express();
const PORT = 3000;

// Serve static files from the "public" directory
app.use(express.static('public'));
app.use(express.json());

// Basic route for testing
app.get('/', (req, res) => {
    res.send('Express server is running!');
});

app.post('/initialize_cache',(req) =>{
    console.log(req.body);
    
})

// Start server
app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});
