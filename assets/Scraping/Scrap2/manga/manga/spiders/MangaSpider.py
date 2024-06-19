import scrapy

class MangaSpider(scrapy.Spider):
    name = "manga_spider"
    start_urls = ["https://myanimelist.net/topmanga.php"]

    def parse(self, response):
        for manga in response.css('tr.ranking-list'):
            rank = manga.css('span.lightLink.top-anime-rank-text::text').get().strip()
            title = manga.css('a.hoverinfo_trigger.fs14.fw-b::text').get()
            manga_link = manga.css('a.hoverinfo_trigger.fs14.fw-b::attr(href)').get()
            publish = manga.css('div.information.di-ib.mt4::text').getall()
            publish_date = publish[1].strip() if len(publish) > 1 else 'Unknown'
            score = manga.css('span.text.on.score-label::text').get()
            image_url = manga.css('img::attr(data-src)').get()

            yield scrapy.Request(
                url=response.urljoin(manga_link),
                callback=self.parse_manga,
                meta={'rank': rank, 
                      'title': title, 
                      'publish': publish_date, 
                      'score': score, 
                      'image_url': image_url
                      }
            )

        # Extract next page URL and pass it to the parse method
        next_page = response.css("a.link-blue-box.next::attr(href)").get()
        if next_page is not None:
            yield response.follow(next_page, callback=self.parse)

    def parse_manga(self, response):
        rank = response.meta['rank']
        title = response.meta['title']
        image_url = response.meta['image_url']
        popularity = response.css('span.numbers.popularity > strong::text').get()
        score = response.meta['score']
        publish = response.meta['publish']

        # Extract authors' names
        authors = response.css('div.spaceit_pad:contains("Authors:") a::text').getall()
        authors = ', '.join(authors)

        # Extract genres
        genres_list = response.css('div.spaceit_pad a::attr(title)').getall()
        genres = ', '.join(genres_list)

        # Extract status and synopsis
        status = response.xpath('//div[contains(span[@class="dark_text"], "Status:")]/text()').get().strip()
        synopsis = response.css('span[itemprop="description"]::text').get()

        # URL for the characters page
        characters_url = response.urljoin(response.css('a[href*="/characters"]').attrib['href'])

        yield scrapy.Request(
            url=characters_url,
            callback=self.parse_characters,
            meta={'rank': rank, 
                  'title': title, 
                  'img': image_url, 
                  'popularity': popularity,
                  'score': score, 
                  'status': status, 
                  'genres': genres, 
                  'publish': publish,
                  'authors': authors, 
                  'synopsis': synopsis
                  }
        )


    def parse_characters(self, response):
        rank = response.meta['rank']
        title = response.meta['title']
        img = response.meta['img']
        popularity = response.meta['popularity']
        score = response.meta['score']
        genres = response.meta['genres']
        publish = response.meta['publish']
        authors = response.meta['authors']
        status = response.meta['status']
        synopsis = response.meta['synopsis']
        characters = response.css('h3.h3_character_name::text').getall()

        yield {
            'rank': rank,
            'title': title,
            'img': img,
            'popularity': popularity,
            'score': score,
            'genres_link': genres,
            'publish': publish,
            'author': authors,
            'status': status,
            'synopsis': synopsis,
            'characters': characters
        }
