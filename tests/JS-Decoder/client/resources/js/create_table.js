// Sample data
const data = [
    { id: 1, open: 10, high: 110, low: 90, close: 105 },
    { id: 2, open: 95, high: 105, low: 92, close: 100 },
    { id: 3, open: 102, high: 115, low: 98, close: 112 },
    // Add more data as needed
];

// Generate the HTML table
function generateTable() {
    const table = document.createElement('table');

    // Create table header
    const thead = document.createElement('thead');
    const headerRow = document.createElement('tr');

    // Column headers
    const headers = ['id', 'open', 'high', 'low', 'close'];
    headers.forEach(headerText => {
        const th = document.createElement('th');
        th.textContent = headerText;
        headerRow.appendChild(th);
    });

    thead.appendChild(headerRow);
    table.appendChild(thead);

    // Create table body
    const tbody = document.createElement('tbody');
    candles.forEach(candle => {
        const row = document.createElement('tr');
        headers.forEach(header => {
            const cell = document.createElement('td');
            cell.textContent = candle[header];
            row.appendChild(cell);
        });
        tbody.appendChild(row);
    });

    table.appendChild(tbody);

    return table;
}

function CreateTable()
{
// Get the container element and append the table
    const container = document.getElementById('tableContainer');
    container.appendChild(generateTable());
}
