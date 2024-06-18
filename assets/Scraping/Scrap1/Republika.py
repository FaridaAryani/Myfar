import requests
from bs4 import BeautifulSoup
from datetime import datetime
import json

# Mengambil waktu sistem saat ini
now = datetime.now()
waktu_pengambilan_data = now.strftime("%d %B %Y %H:%M:%S")
print("Waktu Pengambilan Data:", waktu_pengambilan_data)

url = 'https://republika.co.id/'
req = requests.get(url)
soup = BeautifulSoup(req.text, 'html.parser')
items = soup.find_all('div', 'caption')

data = []  # Untuk menyimpan data
for index, i in enumerate(items[18:], start=1):  # Mulai nomor urutan dari 1
    kategori = i.find('span', 'kanal-info')
    name = i.find('div', 'title')
    waktu = i.find('div', 'date')
    # Memeriksa apakah elemen ditemukan atau tidak
    if name is not None:
        # Jika ditemukan, dapatkan teksnya
        title_text = name.text
        kategori_text = kategori.text if kategori is not None else ""
        waktu_publish = waktu.text
        # Menghapus kategori dari waktu publish
        waktu_publish_cleaned = waktu_publish.replace(kategori.text + ' - ', '')
        # Hapus bagian hari dari waktu publish
        parts = waktu_publish.split(', ')
        if len(parts) > 1:
            waktu_publish_cleaned = ', '.join(parts[1:])
        else:
            waktu_publish_cleaned = waktu_publish

        print("Nomor:", index)
        print("Judul:", title_text)
        print("Kategori:", kategori_text)
        print("Waktu Publish:", waktu_publish_cleaned)

        # Menambahkan data ke dalam list data
        data.append({
            'No' : index,
            'judul': title_text,
            'kategori': kategori_text,
            'waktu_publish': waktu_publish_cleaned,
            'waktu_pengambilan' : waktu_pengambilan_data
        })

    else:
        # Jika tidak ditemukan, cetak pesan atau lakukan tindakan lainnya
        continue  # Untuk melanjutkan ke data selanjutnya

# Menyimpan data ke dalam file JSON
file_path = r'C:\Users\farda\MyWebsite\My\assets\Scraping\Scrap1\DataScrapping.json'
with open(file_path, 'w') as f:
    json.dump(data, f, indent=4)

print("Data telah disimpan dalam file:", file_path)