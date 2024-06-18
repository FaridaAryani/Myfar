from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
import time
import pandas as pd

def scrape_product_page(product_url):
    # Inisialisasi WebDriver untuk membuka halaman produk
    product_driver = webdriver.Chrome(options=options)
    product_driver.get(product_url)

    # Tunggu sampai halaman produk dimuat sepenuhnya
    WebDriverWait(product_driver, 10).until(EC.presence_of_element_located((By.TAG_NAME, 'body')))
    time.sleep(3)  # Sesuaikan waktu tunggu jika diperlukan

    # Scrape data dari halaman produk
    # Misalnya, ambil deskripsi produk atau informasi lainnya yang kamu butuhkan
    # Simpan data yang diambil ke dalam variabel atau tambahkan ke dalam list atau DataFrame

    # Cari elemen span menggunakan XPath untuk rating produk
    rating_element = product_driver.find_element_by_xpath("//span[@data-testid='lblPDPDetailProductRatingNumber']")
    rating_text = rating_element.text

    # Cari elemen p menggunakan XPath untuk teks deskripsi produk
    element_p = product_driver.find_element_by_xpath("//p[@data-unify='Typography']")
    text_p = element_p.text

    # Cari elemen div menggunakan XPath untuk informasi tambahan produk
    element_div = product_driver.find_element_by_xpath("//div[@class='css-1h5fp8g']")
    text_div = element_div.find_element_by_xpath("./span[1]").text

    # Tutup WebDriver setelah selesai scraping halaman produk
    product_driver.quit()

    # Kembalikan data dalam bentuk dictionary
    return {
        'Rating': rating_text,
        'Teks Elemen P': text_p,
        'Teks Elemen Div': text_div
    }

# URL halaman pencarian
url = "https://www.tokopedia.com/search?navsource=&sc=2333&srp_component_id=04.06.00.00&srp_page_id=&srp_page_title=&st=&q=INSTAX"

if url:
    options = webdriver.ChromeOptions()
    options.add_argument("--start-maximized")
    driver = webdriver.Chrome(options=options)
    driver.get(url)

    data = []
    page_num = 1
    num_page = 20  # Jumlah halaman yang ingin di-scrape

    while num_page >= page_num:
        # Tunggu hingga elemen container produk muncul
        WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.CLASS_NAME, 'css-llwpbs')))

        # Scroll ke bawah untuk memuat lebih banyak produk
        last_height = driver.execute_script("return document.body.scrollHeight")
        while True:
            driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
            time.sleep(2)
            new_height = driver.execute_script("return document.body.scrollHeight")
            if new_height == last_height:
                break
            last_height = new_height

        # Gunakan BeautifulSoup untuk mengambil konten halaman
        soup = BeautifulSoup(driver.page_source, "html.parser")
        containers = soup.findAll('div', attrs={'class': 'css-llwpbs'})
        print(f"Ditemukan {len(containers)} kontainer pada halaman {page_num}")  # Baris debug

        # Iterasi melalui setiap kontainer produk
        for container in containers:
            try:
                # Ambil informasi produk dari kontainer menggunakan BeautifulSoup
                nama_produk = container.find('div', attrs={'class': 'prd_link-product-name css-3um8ox'})
                link_produk = container.find('a')
                link_gambar = container.find('img')
                harga_produk = container.find('div', attrs={'class': 'prd_link-product-price css-h66vau'})
                harga_sebelum_diskon = container.find('div', attrs={'class': 'prd_label-product-slash-price css-xfl72w'})
                persentase_diskon_elements = container.find_all('div', attrs={'class': 'prd_badge-product-discount css-1xelcdh'})
                apakah_iklan = container.find('span', attrs={'class': 'css-1sbv0b9'})
                nama_toko = container.find('span', attrs={'class': 'prd_link-shop-name css-1kdc32b flip'})
                lokasi_toko = container.find('span', attrs={'class': 'prd_link-shop-loc css-1kdc32b flip'})
                rating = container.find('span', attrs={'class': 'prd_rating-average-text css-t70v7i'})
                jumlah_terjual = container.find('span', attrs={'class': 'prd_label-integrity css-1sgek4h'})

                # Cek apakah elemen yang dibutuhkan ada, lalu ambil teksnya
                nama_produk_text = nama_produk.text.strip() if nama_produk else ''
                link_produk_href = link_produk.get('href', '') if link_produk else ''
                link_gambar_src = link_gambar.get('src', '') if link_gambar else ''
                harga_produk_text = harga_produk.text.strip() if harga_produk else ''
                harga_sebelum_diskon_text = harga_sebelum_diskon.text.strip() if harga_sebelum_diskon else ''
                persentase_diskon_text = ', '.join([element.text.strip() for element in persentase_diskon_elements]) if persentase_diskon_elements else ''
                apakah_iklan_text = apakah_iklan.text.strip() if apakah_iklan else ''
                nama_toko_text = nama_toko.text.strip() if nama_toko else ''
                lokasi_toko_text = lokasi_toko.text.strip() if lokasi_toko else ''
                rating_text = rating.text.strip() if rating else ''
                jumlah_terjual_text = jumlah_terjual.text.strip() if jumlah_terjual else ''

                # Append detail produk ke dalam list data jika semua field yang dibutuhkan ada
                if nama_produk_text and link_produk_href and link_gambar_src and harga_produk_text and apakah_iklan_text.lower() != 'ad' and nama_produk_text.lower() != 'refill':
                    # Lakukan scraping halaman produk dan tambahkan data
                    product_data = scrape_product_page(link_produk_href)
                    data.append({
                        'Nama Produk': nama_produk_text,
                        'Link Produk': link_produk_href,
                        'Link Gambar': link_gambar_src,
                        'Harga Produk': harga_produk_text,
                        'Diskon': persentase_diskon_text,
                        'Harga Sebelum Diskon': harga_sebelum_diskon_text,
                        'Nama Toko': nama_toko_text,
                        'Lokasi Toko': lokasi_toko_text,
                        'Rating': rating_text,
                        'Jumlah Terjual': jumlah_terjual_text,
                        **product_data  # Gabungkan data produk ke dalam dictionary utama
                    })

            except AttributeError as e:
                print(f"Error: {e}")  # Baris debug
                continue

        # Klik tombol halaman berikutnya
        try:
            next_button = driver.find_element(By.CSS_SELECTOR, "button[aria-label^='Laman berikutnya']")
            next_button.click()
            WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.CLASS_NAME, 'css-llwpbs')))
            page_num += 1
        except:
            print("Tidak ada halaman lain untuk di-scrape.")
            break

    # Cetak atau simpan data yang telah diambil ke dalam Excel
    print(data)
    file_path = r"C:\Users\farda\MyWebsite\My\assets\Scraping\Scrap3\Scraper.json"  # Ganti dengan path yang diinginkan
    df = pd.DataFrame(data)
    df.to_excel(file_path, index=False)
    driver.quit()  # Tutup browser