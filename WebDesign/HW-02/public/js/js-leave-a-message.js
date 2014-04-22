function isEmpty(val) {
    return ((val == '') || (val == null));
}//isEmpty(val)

function formcheck(form) {
    if(isEmpty(form.name.value) ||
            isEmpty(form.email.value))
    {
        window.alert("Please fullfil the form!");
        return false;
    }//if
    return true;
}//formcheck(form)

function showAllMessages() {
    var xmlhttp = new XMLHttpRequest();

    xmlhttp.onreadystatechange = function() {
        if(xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            document.getElementById("div-allMessages").innerHTML = xmlhttp.responseText;
        }//if
    };//lambda

    xmlhttp.open("GET", "../cgi-bin/show-all-message.cgi", true); 
    xmlhttp.send();
}//showAllMessages()

// --------------------------------------------------

$(document).ready(function() {
    
});

