$(".menu>li").mouseover(
    function(){
        $(this).find(".submenu").stop().slideDown(200);
    }
);
$(".menu>li").mouseleave(
    function(){
        $(this).find(".submenu").stop().slideUp(200);
    }
);

var slideimg = $(".slide>div");
var lastno = 4;
var startno= 0;

function play(){
    $(slideimg[startno]).animate({left: "-100vw"}, 3000, 
    function(){$(this).css({left: "100vw"});});
    startno++;
    if (startno==lastno) {
        startno = 0;
    }
    $(slideimg[startno]).animate({left: "0"}, 3000);
}

var timer = setInterval(function(){play();},4000);

$(".popup4>button").click(
    function(){
        $(".popup").hide();
    }
);
$(".nowifi").click(
    function(){
        $(".popup").show();
    }
);

var $leftMenu = $('.left-menu');

function updateMenuPosition() {
    var scrollTop = $(window).scrollTop();
    var menuHeight = $leftMenu.outerHeight();
    var windowHeight = $(window).height();

    var topPosition = scrollTop + (windowHeight - menuHeight) / 2;

    $leftMenu.css('top', topPosition + 'px');
}

$(window).on('scroll resize', updateMenuPosition);

updateMenuPosition();


$(window).scroll(function() {
    var scrollDistance = $(window).scrollTop();

    $('section').each(function(i) {
        if ($(this).position().top <= scrollDistance) {
            $('.left-menu a.active').removeClass('active');
            $('.left-menu a').eq(i + 1).addClass('active');
        }
    });
}).scroll();

$(document).ready(function() {
    const sections = $('section');
    const navLi = $('#sidebar ul li a');

    let current = sections.first().attr('id');
    navLi.removeClass('active');
    navLi.each(function() {
        if ($(this).attr('href') === `#${current}`) {
            $(this).parent().addClass('active');
        }
    });

    $(window).on('scroll', function() {
        let current = "";

        sections.each(function() {
            const sectionTop = $(this).offset().top;
            const sectionHeight = $(this).outerHeight();
            if ($(window).scrollTop() >= sectionTop - sectionHeight / 3) {
                current = $(this).attr('id');
            }
        });

        navLi.parent().removeClass('active');
        navLi.each(function() {
            if ($(this).attr('href') === `#${current}`) {
                $(this).parent().addClass('active');
            }
        });
    });
});


$('.left-menu a').on('click', function(event) {
    if (this.hash !== "") {
        event.preventDefault();
        var hash = this.hash;

        $('html, body').animate({
            scrollTop: $(hash).offset().top + 80
        }, 800);
    }
});