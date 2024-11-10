const express = require('express');


const app = express();
const PORT = 3000;

app.use(express.static('public'));
app.use(express.json());

app.post('/initialize_cache', (req, res) => {
    const { capacity } = req.body;

    // Run the C++ executable with the capacity as an argument
   
});

app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});
