from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from webdriver_manager.chrome import ChromeDriverManager

# Opsi untuk menjalankan Chrome tanpa GUI
chrome_options = Options()
chrome_options.add_argument("--headless")  # Opsional: gunakan headless mode

# Inisialisasi WebDriver
service = Service(ChromeDriverManager().install())
driver = webdriver.Chrome(service=service, options=chrome_options)

try:
    # Buka halaman web
    url = "https://www.tokopedia.com/instax-official/fujifilm-instax-mini-12-instant-camera-pastel-blue?extParam=ivf%3Dtrue&src=topads"
    driver.get(url)

    # Tunggu hingga elemen yang diinginkan tersedia
    wait = WebDriverWait(driver, 20)  # Tunggu hingga 20 detik

    # Menggunakan XPath untuk mengambil URL gambar
    product_image_element = wait.until(EC.presence_of_element_located((By.XPATH, '//img[@class="css-1c345mg N8xmpVrww3v8HjDVw7D5rg=="]')))
    product_image_url = product_image_element.get_attribute('src')

    # Cetak URL gambar
    print("Product Image URL:", product_image_url)

finally:
    # Jangan lupa untuk menutup driver
    driver.quit()
