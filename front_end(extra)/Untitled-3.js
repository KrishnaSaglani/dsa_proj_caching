// Function to send a key-value pair to the server and update cache table
async function putData() {
    const key = document.getElementById('key').value;
    const value = document.getElementById('value').value;

    if (key && value) {
        // Send key-value to server
        await fetch('/data', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({ key, value })
        });

        displayCache(); // Update cache display
    } else {
        alert("Please enter both key and value");
    }
}

// Function to fetch cache contents and display them in the table
async function displayCache() {
    const response = await fetch('/cache');
    const cacheData = await response.json();

    const cacheContents = document.getElementById('cache-contents');
    cacheContents.innerHTML = "";  // Clear the table before updating

    for (const [key, value] of Object.entries(cacheData)) {
        const row = document.createElement('tr');
        
        // Create and append key cell
        const keyCell = document.createElement('td');
        keyCell.textContent = key;
        row.appendChild(keyCell);

        // Create and append value cell
        const valueCell = document.createElement('td');
        valueCell.textContent = value;
        row.appendChild(valueCell);

        // Create and append timestamp cell
        const timestampCell = document.createElement('td');
        timestampCell.textContent = new Date().toLocaleString(); // Placeholder timestamp
        row.appendChild(timestampCell);

        cacheContents.appendChild(row);
    }
}
