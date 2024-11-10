const express = require('express');
const { exec } = require('child_process');

const app = express();
const PORT = 3000;

app.use(express.static('public'));
app.use(express.json());

app.post('/initialize_cache', (req, res) => {
    const { capacity } = req.body;

    // Run the C++ executable with the capacity as an argument
    exec(`./lru_cache ${capacity}`, (error, stdout, stderr) => {
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

        // Parse the metrics data from the stdout
        const [hitRate, accessTime, evictionCount] = stdout.trim().split('\n');
        res.json({
            hitRate: hitRate.trim(),
            accessTime: accessTime.trim(),
            evictionCount: evictionCount.trim()
        });
    });
});

app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});
