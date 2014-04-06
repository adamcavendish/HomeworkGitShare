function hidePopupWindowAndShadow() {
    document.getElementById('Popup-Window').style.display='none';
    document.getElementById('Shadow').style.display='none';
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

    $('#Popup-Window').css('z-index', 1);
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

// --------------------------------------------------

$(document).ready(function() {
    readyNavigationBar();
    readyNewsScrollArea();
    readyResizeMap($('#BottleImg').get(0), $('#BottleMap').get(0), 1920, 1200);
});

