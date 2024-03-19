#include "server/frontend.h"

const char index_html[] = R"rawliteral(
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Voice Recorder</title>
</head>
<body>
    <div id="startBlock">
        <input type="text" id="filename"/>
        <button id="startRecord" onclick="onStartRecord()">Start record</button>
    </div>

    <div id="recordingBlock" hidden>
        <p id="recordingMsg">
            Recording<br>
            <button id="startRecord" onclick="onEndRecord()">Stop record</button>
        </p>
    </div>

    <div id="resultBlock" hidden>
        <p id="recordingMsg">
            The file was recorded. File: <b>"<span id="finalFilename"></span>"</b>.<br>
            <a id="fileLink">download this file</a>
        </p>
    </div>

    <br>
    <div id="filesBlock">
        <table id="fileTable">
            <thead>
                <tr>
                    <td>Filename</td>
                    <td>Mode</td>
                </tr>
            </thead>
            <tbody>
            </tbody>
        </table>
    </div>

    <script>
        var curFilename = "";

        function getCurDateString() {
            var currentDate = new Date();
            var format = (value) => String(value).padStart(2, '0');

            var year = currentDate.getFullYear();
            var month = String(currentDate.getMonth() + 1).padStart(2, '0');
            var day = String(currentDate.getDate()).padStart(2, '0');
            var hours = String(currentDate.getHours()).padStart(2, '0');
            var minutes = String(currentDate.getMinutes()).padStart(2, '0');
            var seconds = String(currentDate.getSeconds()).padStart(2, '0');

            return `${day}_${month}_${year}_${hours}${minutes}${seconds}.saso`;
        }

        function getDownloadLink(filename) {
            return `/download?filename=${filename}`;
        }

        function downloadFile(filename) {
            var xhr = new XMLHttpRequest();
            xhr.open("GET", getDownloadLink(filename), true);
            xhr.send(null);
        }

        function downloadClick(filename) {
            console.log(filename);
            downloadFile(filename)
        }

        function addFileToTable(filename) {
            var newRow = `<tr><td>${filename}</td><td><button id="${filename}" onclick="downloadClick(this.id)">D</button></td></tr>`;
            var tableRef = document.getElementById('fileTable');
            let row = tableRef.insertRow(-1);
            row.innerHTML = newRow;
        }

        function getFilenameOrDefault() {
            var out = document.getElementById("filename").value;
            return out === "" ? getCurDateString() : out + ".saso";
        }

        function onStartRecord() {
            curFilename = getFilenameOrDefault();
            document.getElementById("startBlock").hidden = true;
            document.getElementById("recordingBlock").hidden = false;
            document.getElementById("resultBlock").hidden = true;

            var xhr = new XMLHttpRequest();
            xhr.open("GET", `/recordingStart?filename=${curFilename}`, true);
            xhr.send(null);
        }

        function onEndRecord() {
            document.getElementById("startBlock").hidden = false;
            document.getElementById("recordingBlock").hidden = true;
            document.getElementById("resultBlock").hidden = false;
            document.getElementById("finalFilename").innerHTML = curFilename;
            addFileToTable(curFilename);
            document.getElementById("fileLink").href = getDownloadLink(curFilename);

            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/recordingStop", true);
            xhr.send(null);
        }
    </script>
</body>
</html>
)rawliteral";
