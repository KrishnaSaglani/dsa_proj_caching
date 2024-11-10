const express = require('express');
const { exec } = require('child_process');
const app = express();
const PORT = 3000;

// Serve static files from the "public" directory
app.use(express.static('public'));
app.use(express.json());

// Basic route for testing
app.get('/', (req, res) => {
    res.send('Express server is running!');
});

app.post('/initialize_cache',(req,res) =>{
    console.log(req.body);

    console.log("Helloworld");
    const {capacity} = req.body
    
    exec(`.\\stacked_file.exe ${capacity}`, (error, stdout, stderr) => {
        
        if (error) {
            console.error(`Error executing C++ program: ${error.message}`);
            res.status(500).json({ error: 'Failed to initialize cache' });
            return;
        }
        if (stderr) {
            console.error(`Stderr: ${stderr}`);
            res.status(500).json({ error: 'Error in C++ program' });
            return;
        }

        console.log(stdout);
        

        // Parse the metrics data from the stdout
        const [hitRate, accessTime, evictionCount] = stdout.trim().split('\n');
        console.log(hitRate,accessTime,evictionCount);
        
        res.json({
            hitRate: hitRate.trim(),
            accessTime: accessTime.trim(),
            evictionCount: evictionCount.trim()
        });
    });
    
})

// Start server
app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});
