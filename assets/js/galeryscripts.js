document.addEventListener("DOMContentLoaded", function() {
    const slides = document.querySelectorAll(".image-slide");
    let currentSlide = 0;

    function showSlide(index) {
        slides.forEach((slide, idx) => {
            if (idx === index) {
                slide.classList.add("active");
            } else {
                slide.classList.remove("active");
            }
        });
    }

    function nextSlide() {
        currentSlide = (currentSlide + 1) % slides.length;
        showSlide(currentSlide);
    }

    // Auto transition every 3 seconds
    setInterval(nextSlide, 3000);
});
