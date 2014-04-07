function hidePopupWindowAndShadow() {
    document.getElementById('Popup-Window').style.display='none';
    document.getElementById('Shadow').style.display='none';
    $('html').css('overflow', 'auto');
    $('body').css('overflow', 'auto');    
}

function readyResizeMap(img, map, originalWidth, originalHeight) {
    var areas = map.getElementsByTagName('area');
    var areasLen = areas.length;
    
    var scaleW = img.width / originalWidth;
    var scaleH = img.height / originalHeight;
    
    var coords = Array.prototype.map.call(areas, function(i) {
        return i.coords;
    });
    for(var i = 0; i < areasLen; ++i) {
        var coordsArr = coords[i].split(',').map(Number);
        coordsArr[0] *= scaleW;
        coordsArr[1] *= scaleH;
        coordsArr[2] *= scaleW;
        coordsArr[3] *= scaleH;
        areas[i].coords = coordsArr.map(Math.floor).join(',');
    }
}

function readyNavigationBar() {
    var $navbar = $('#navigation-bar');
    $navbar.hover(
        function() { $(this).addClass('iehover'); },
        function() { $(this).removeClass('iehover'); }
    );

    // get the navigation-bar to the center
    var w = 0;
    $('#navigation-bar ul li').each(function(idx, item) {
       w += parseInt($(item).css('width'));
    });
    $navbar.width(w);
    $navbar.css({ 'margin': 'auto' });
}

function readyNewsScrollArea() {
    var scrtime = null;
    var $con = $('#News');
    var $ul = $('#News ul');

    $con.hover(function() {
        clearInterval(scrtime);
    }, function() {
        scrtime = setInterval(function() {
            var $li = $('#News ul li');
            var $item = $li.last();
            $item.prependTo($ul);
            $item.hide();
            $item.fadeIn(2000);
        }, 1500);
    }).trigger('mouseleave');
}

function readyAdAndListenOnScroll() {
    function adfunc(ev) { window.open('http://www.github.com'); }

    var $Ad1 = $('#FloatingAd1');
    var $Ad2 = $('#FloatingAd2');
    $Ad1.unbind().click(adfunc);
    $Ad2.unbind().click(adfunc);

    $(window).scroll(function() {
        var topVal = $(document).scrollTop();
        $Ad1.css({ top: topVal });
        $Ad2.css({ top: topVal });
    });
}

function readyPopupWindow() {
    var $Shadow = $('#Shadow');
    $('#Popup-Window').css('z-index', 1001);
    $Shadow.css('z-index', 1000);
    $Shadow.css({ 'width': $('body').width, 'height': $('body').height });
    $('html').css('overflow', 'hidden');
    $('body').css('overflow', 'hidden');
}

// --------------------------------------------------

$(document).ready(function() {
    readyNavigationBar();
    readyNewsScrollArea();
    readyAdAndListenOnScroll();
    readyResizeMap($('#BottleImg').get(0), $('#BottleMap').get(0), 1920, 1200);
    readyPopupWindow();
});

