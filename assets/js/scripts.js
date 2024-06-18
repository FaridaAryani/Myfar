// Menambahkan event listener untuk form submit
document.getElementById('projectForm').addEventListener('submit', function(event) {
    event.preventDefault(); // Mencegah form dari pengiriman

    const selectedProject = document.getElementById('project').value; // Mengambil nilai proyek yang dipilih dari dropdown
    const projects = document.querySelectorAll('.project'); // Mengambil semua elemen dengan class 'project'

    // Sembunyikan semua proyek
    projects.forEach(project => {
        project.style.display = 'none'; // Mengatur display menjadi 'none' untuk menyembunyikan elemen
    });

    // Tampilkan proyek yang dipilih
    const selectedElement = document.getElementById(selectedProject); // Mengambil elemen proyek yang dipilih berdasarkan id
    if (selectedElement) {
        selectedElement.style.display = 'block'; // Mengatur display menjadi 'block' untuk menampilkan elemen
    }

    // Jika proyek yang dipilih adalah Tic Tac Toe, buat papan permainan
    if (selectedProject === 'tic-tac-toe') {
        // Mendefinisikan konstanta untuk kelas X, O dan kombinasi kemenangan
        const X_CLASS = 'x';
        const O_CLASS = 'o';
        const WINNING_COMBINATIONS = [
            [0, 1, 2],
            [3, 4, 5],
            [6, 7, 8],
            [0, 3, 6],
            [1, 4, 7],
            [2, 5, 8],
            [0, 4, 8],
            [2, 4, 6]
        ];

        // Mengambil elemen sel, papan, hasil, tombol restart, dan input nama dari DOM
        const cellElements = document.querySelectorAll('[data-cell]');
        const board = document.getElementById('board');
        const resultElement = document.getElementById('result');
        const restartButton = document.getElementById('restartButton');
        const nameInput = document.getElementById('name-input');
        let oTurn; // Menyimpan giliran pemain

        startGame(); // Memulai permainan

        // Menambahkan event listener untuk tombol restart
        restartButton.addEventListener('click', startGame);

        function startGame() {
            oTurn = false; // Mengatur giliran awal ke pemain X
            cellElements.forEach(cell => {
                cell.classList.remove(X_CLASS); // Menghapus kelas X dari sel
                cell.classList.remove(O_CLASS); // Menghapus kelas O dari sel
                cell.removeEventListener('click', handleClick); // Menghapus event listener sebelumnya
                cell.addEventListener('click', handleClick, { once: true }); // Menambahkan event listener baru untuk sekali klik
            });
            setBoardHoverClass(); // Mengatur hover class pada papan
            resultElement.textContent = ''; // Mengosongkan teks hasil
            nameInput.value = ''; // Mengosongkan input nama
        }

        function handleClick(e) {
            const cell = e.target; // Mengambil elemen sel yang diklik
            const currentClass = oTurn ? O_CLASS : X_CLASS; // Menentukan kelas yang akan ditambahkan (X atau O)
            placeMark(cell, currentClass); // Menempatkan tanda pada sel
            if (checkWin(currentClass)) { // Memeriksa kemenangan
                endGame(false); // Mengakhiri permainan dengan kemenangan
            } else if (isDraw()) { // Memeriksa hasil seri
                endGame(true); // Mengakhiri permainan dengan hasil seri
            } else {
                swapTurns(); // Mengganti giliran pemain
                setBoardHoverClass(); // Mengatur hover class pada papan
            }
        }

        function endGame(draw) {
            const userName = nameInput.value.trim(); // Mengambil nama pemain
            if (draw) {
                resultElement.textContent = 'Draw!'; // Menampilkan hasil seri
            } else {
                resultElement.textContent = `${oTurn ? "O" : "X"} Wins! ${userName ? "Player: " + userName : ""}`; // Menampilkan pemenang dan nama pemain
            }
        }

        function isDraw() {
            return [...cellElements].every(cell => {
                return cell.classList.contains(X_CLASS) || cell.classList.contains(O_CLASS); // Memeriksa apakah semua sel terisi
            });
        }

        function placeMark(cell, currentClass) {
            cell.classList.add(currentClass); // Menambahkan kelas (X atau O) ke sel
        }

        function swapTurns() {
            oTurn = !oTurn; // Mengganti giliran pemain
        }

        function setBoardHoverClass() {
            board.classList.remove(X_CLASS); // Menghapus kelas hover X dari papan
            board.classList.remove(O_CLASS); // Menghapus kelas hover O dari papan
            if (oTurn) {
                board.classList.add(O_CLASS); // Menambahkan kelas hover O jika giliran O
            } else {
                board.classList.add(X_CLASS); // Menambahkan kelas hover X jika giliran X
            }
        }

        function checkWin(currentClass) {
            return WINNING_COMBINATIONS.some(combination => {
                return combination.every(index => {
                    return cellElements[index].classList.contains(currentClass); // Memeriksa apakah ada kombinasi kemenangan
                });
            });
        }

    } else if (selectedProject === 'scrap1'){
        // Menggunakan jQuery untuk mengambil data dari file JSON dan menampilkan dalam bentuk tabel
        $(function(){
            $.get('assets/Scraping/Scrap1/DataScrapping.json', function(obj) {
                var str = "<table border=1>"; // Membuat string awal untuk tabel
                str += "<tr><th>No</th><th>Judul</th><th>Kategori</th><th>Waktu Publikasi</th><th>Waktu Pengambilan</th></tr>"; // Menambahkan header tabel
                $.each(obj, function(n, data) {
                    str += "<tr><td>" + (n + 1) + "</td>"; // Menambahkan nomor urut
                    str += "<td>" + data.judul + "</td>"; // Menambahkan judul
                    str += "<td>" + data.kategori + "</td>"; // Menambahkan kategori
                    str += "<td>" + data.waktu_publish + "</td>"; // Menambahkan waktu publikasi
                    str += "<td>" + data.waktu_pengambilan + "</td></tr>"; // Menambahkan waktu pengambilan
                });
                str += "</table>"; // Menutup tag tabel
                $('#table').html(str); // Menampilkan tabel di elemen dengan id 'table'
            });
        });
    } else if (selectedProject === 'scrap2'){
        const table = document.getElementById('table'); // Implementasi untuk proyek scrap2
    } else if (selectedProject === 'scrap3'){
        const table = document.getElementById('table'); // Implementasi untuk proyek scrap3
    } else if (selectedProject === 'tree'){
        const table = document.getElementById('table'); // Implementasi untuk proyek tree
    } else if (selectedProject === 'MoneyTracker'){
        const table = document.getElementById('table'); // Implementasi untuk Money Tracker
    }
});