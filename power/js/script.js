let isSidebarExpanded = true;

function toggleSidebar() {
  const sidebar = document.querySelector('.expandable-sidebar');
  sidebar.style.display = isSidebarExpanded ? 'none' : 'block';
  isSidebarExpanded = !isSidebarExpanded;
}

function queryLogFile() {
  const metric = document.getElementById('logMetricSelect').value;
  fetch('../log/log_file.txt')
    .then(response => response.text())
    .then(data => {
      const lines = data.split('\n').map(line => JSON.parse(line));
      const metricData = lines.map(entry => entry[metric]);
      updateDynamicGraph(metricData);
    });
}

function updateDynamicGraph(metricData) {
  const usageCanvas = document.getElementById('usageGraph');
  const usageCtx = usageCanvas.getContext('2d');
  usageCtx.clearRect(0, 0, usageCanvas.width, usageCanvas.height);
  usageCtx.beginPath();
  usageCtx.moveTo(0, usageCanvas.height);

  metricData.forEach((value, index) => {
    const x = (usageCanvas.width / metricData.length) * index;
    const y = usageCanvas.height - (value / Math.max(...metricData)) * usageCanvas.height;
    usageCtx.lineTo(x, y);
  });

  usageCtx.strokeStyle = 'orange';
  usageCtx.stroke();
}