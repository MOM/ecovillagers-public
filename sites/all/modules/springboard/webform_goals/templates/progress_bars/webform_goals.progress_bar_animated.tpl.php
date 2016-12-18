<script type="text/javascript">
<?php
if ($drupal) {
?>

(function ($) {

  Drupal.behaviors.webformgoals = {
    attach: function (context, settings) {

$(function() {
  $('.progressbar').each(function(){
    var t = $(this),
      dataperc = t.attr('data-perc'),
      barperc = Math.round(dataperc*5.56);
    t.find('.bar').animate({width:barperc}, dataperc*25);
    t.find('.label').append('<div class="perc"></div>');

    function perc() {
      var length = t.find('.bar').css('width'),
        perc = Math.round(parseInt(length)/5.56),
        labelpos = (parseInt(length)-2);
      t.find('.label').css('left', labelpos);
      t.find('.perc').text(perc+'%');
    }
    perc();
    setInterval(perc, 0);
  });
});



    }
  };

})(jQuery);


<?php
}
else {
?>
$(function() {
  $('.progressbar').each(function(){
    var t = $(this),
      dataperc = t.attr('data-perc'),
      barperc = Math.round(dataperc*5.56);
    t.find('.bar').animate({width:barperc}, dataperc*25);
    t.find('.label').append('<div class="perc"></div>');

    function perc() {
      var length = t.find('.bar').css('width'),
        perc = Math.round(parseInt(length)/5.56),
        labelpos = (parseInt(length)-2);
      t.find('.label').css('left', labelpos);
      t.find('.perc').text(perc+'%');
    }
    perc();
    setInterval(perc, 0);
  });
});
<?php
}
?>
</script>
<!-- http://cssdeck.com/labs/nice-sparkle-progress-bars -->
<style type="text/css">
.progressbar{
    position:relative;
    display:block;
}
/* black inner area. */
.progressbar:before{
 position:relative;
  display:block;
  content:"";
  width:558px;
  height:18px;
  top:10px;
  left:20px;
  -webkit-border-radius:20px;
  border-radius:20px;
  background:#222;
  -webkit-box-shadow: inset 0px 0px 6px 0px rgba(0, 0, 0, 0.85);;
  box-shadow: inset 0px 0px 6px 0px rgba(0, 0, 0, 0.85);
  border:1px solid rgba(0,0,0,0.8);
  margin-bottom:20px;
}
.bar {
  position:absolute;
  display:block;
  width:0px;
  height:16px;
  top:12px;
  left:22px;
  background: rgb(126,234,25);
  background: -moz-linear-gradient(top,  rgba(126,234,25,1) 0%, rgba(83,173,0,1) 100%);
  background: -webkit-gradient(linear, left top, left bottom, color-stop(0%,rgba(126,234,25,1)), color-stop(100%,rgba(83,173,0,1)));
  background: -webkit-linear-gradient(top,  rgba(126,234,25,1) 0%,rgba(83,173,0,1) 100%);
  background: -o-linear-gradient(top,  rgba(126,234,25,1) 0%,rgba(83,173,0,1) 100%);
  background: -ms-linear-gradient(top,  rgba(126,234,25,1) 0%,rgba(83,173,0,1) 100%);
  background: linear-gradient(to bottom,  rgba(126,234,25,1) 0%,rgba(83,173,0,1) 100%);
  filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#7eea19', endColorstr='#53ad00',GradientType=0 );
  -webkit-border-radius:16px;
  border-radius:16px;
  overflow:hidden;
}
.bar.color4 {
  background: rgb(24,50,226);
  background: -moz-linear-gradient(top,  rgba(24,109,226,1) 0%, rgba(0,69,165,1) 100%);
  background: -webkit-gradient(linear, left top, left bottom, color-stop(0%,rgba(24,109,226,1)), color-stop(100%,rgba(0,69,165,1)));
  background: -webkit-linear-gradient(top,  rgba(24,109,226,1) 0%,rgba(0,69,165,1) 100%);
  background: -o-linear-gradient(top,  rgba(24,109,226,1) 0%,rgba(0,69,165,1) 100%);
  background: -ms-linear-gradient(top,  rgba(24,109,226,1) 0%,rgba(0,69,165,1) 100%);
  background: linear-gradient(to bottom,  rgba(24,109,226,1) 0%,rgba(0,69,165,1) 100%);
  filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#186de2', endColorstr='#0045a5',GradientType=0 );
  -webkit-box-shadow: 0px 0px 12px 0px rgba(24, 109, 226, 1),inset 0px 1px 0px 0px rgba(255, 255, 255, 0.45),inset 1px 0px 0px 0px rgba(255, 255, 255, 0.25),inset -1px 0px 0px 0px rgba(255, 255, 255, 0.25);
  box-shadow: 0px 0px 12px 0px rgba(24, 109, 226, 1),inset 0px 1px 0px 0px rgba(255, 255, 255, 0.45),inset 1px 0px 0px 0px rgba(255, 255, 255, 0.25),inset -1px 0px 0px 0px rgba(255, 255, 255, 0.25);
}
.bar:before {
  position:absolute;
  display:block;
  content:"";
  width:606px;
  height:150%;
  top:-25%;
  left:-25px;
  background: -moz-radial-gradient(center, ellipse cover,  rgba(255,255,255,0.35) 0%, rgba(255,255,255,0.01) 50%, rgba(255,255,255,0) 51%, rgba(255,255,255,0) 100%);
  background: -webkit-gradient(radial, center center, 0px, center center, 100%, color-stop(0%,rgba(255,255,255,0.35)), color-stop(50%,rgba(255,255,255,0.01)), color-stop(51%,rgba(255,255,255,0)), color-stop(100%,rgba(255,255,255,0)));
  background: -webkit-radial-gradient(center, ellipse cover,  rgba(255,255,255,0.35) 0%,rgba(255,255,255,0.01) 50%,rgba(255,255,255,0) 51%,rgba(255,255,255,0) 100%);
  background: -o-radial-gradient(center, ellipse cover,  rgba(255,255,255,0.35) 0%,rgba(255,255,255,0.01) 50%,rgba(255,255,255,0) 51%,rgba(255,255,255,0) 100%);
  background: -ms-radial-gradient(center, ellipse cover,  rgba(255,255,255,0.35) 0%,rgba(255,255,255,0.01) 50%,rgba(255,255,255,0) 51%,rgba(255,255,255,0) 100%);
  background: radial-gradient(ellipse at center,  rgba(255,255,255,0.35) 0%,rgba(255,255,255,0.01) 50%,rgba(255,255,255,0) 51%,rgba(255,255,255,0) 100%);
  filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#59ffffff', endColorstr='#00ffffff',GradientType=1 );
}

.bar:after {
  position:absolute;
  display:block;
  content:"";
  width:64px;
  height:16px;
  right:0;
  top:0;
  -webkit-border-radius: 0px 16px 16px 0px;
  border-radius: 0px 16px 16px 0px;
  background: -moz-linear-gradient(left,  rgba(255,255,255,0) 0%, rgba(255,255,255,0.6) 98%, rgba(255,255,255,0) 100%);
  background: -webkit-gradient(linear, left top, right top, color-stop(0%,rgba(255,255,255,0)), color-stop(98%,rgba(255,255,255,0.6)), color-stop(100%,rgba(255,255,255,0)));
  background: -webkit-linear-gradient(left,  rgba(255,255,255,0) 0%,rgba(255,255,255,0.6) 98%,rgba(255,255,255,0) 100%);
  background: -o-linear-gradient(left,  rgba(255,255,255,0) 0%,rgba(255,255,255,0.6) 98%,rgba(255,255,255,0) 100%);
  background: -ms-linear-gradient(left,  rgba(255,255,255,0) 0%,rgba(255,255,255,0.6) 98%,rgba(255,255,255,0) 100%);
  background: linear-gradient(to right,  rgba(255,255,255,0) 0%,rgba(255,255,255,0.6) 98%,rgba(255,255,255,0) 100%);
  filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#00ffffff', endColorstr='#00ffffff',GradientType=1 );
  opacity:0.2;
}
.label {
  font-family: 'Aldrich', sans-serif;
  position:absolute;
  display:block;
  width:40px;
  height:30px;
  line-height:30px;
  top:38px;
  left:0px;
  background: rgb(76,76,76);
  background: -moz-linear-gradient(top,  rgba(76,76,76,1) 0%, rgba(38,38,38,1) 100%);
  background: -webkit-gradient(linear, left top, left bottom, color-stop(0%,rgba(76,76,76,1)), color-stop(100%,rgba(38,38,38,1)));
  background: -webkit-linear-gradient(top,  rgba(76,76,76,1) 0%,rgba(38,38,38,1) 100%);
  background: -o-linear-gradient(top,  rgba(76,76,76,1) 0%,rgba(38,38,38,1) 100%);
  background: -ms-linear-gradient(top,  rgba(76,76,76,1) 0%,rgba(38,38,38,1) 100%);
  background: linear-gradient(to bottom,  rgba(76,76,76,1) 0%,rgba(38,38,38,1) 100%);
  filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#4c4c4c', endColorstr='#262626',GradientType=0 );
  font-weight:bold;
  font-size:12px;
  color:#fff;
  text-align:center;
  -webkit-border-radius:6px;
  border-radius:6px;
  border:1px solid rgba(0,0,0,0.2);
  -webkit-box-shadow: 0px 1px 4px 0px rgba(0, 0, 0, 0.3);
  box-shadow: 0px 1px 4px 0px rgba(0, 0, 0, 0.3);
  text-shadow: 0px -1px 0px #000000,0px 1px 1px #000000;
  filter: dropshadow(color=#000000, offx=0, offy=-1);
}
.label span {
  position:absolute;
  display:block;
  width:12px;
  height:9px;
  top:-9px;
  left:14px;
  background:transparent;
  overflow:hidden;
}
.label span:before {
  position:absolute;
  display:block;
  content:"";
  width:8px;
  height:8px;
  top:4px;
  left:2px;
  border:1px solid rgba(0,0,0,0.5);
  background: rgb(86,86,86);
  background: -moz-linear-gradient(-45deg,  rgba(86,86,86,1) 0%, rgba(76,76,76,1) 50%);
  background: -webkit-gradient(linear, left top, right bottom, color-stop(0%,rgba(86,86,86,1)), color-stop(50%,rgba(76,76,76,1)));
  background: -webkit-linear-gradient(-45deg,  rgba(86,86,86,1) 0%,rgba(76,76,76,1) 50%);
  background: -o-linear-gradient(-45deg,  rgba(86,86,86,1) 0%,rgba(76,76,76,1) 50%);
  background: -ms-linear-gradient(-45deg,  rgba(86,86,86,1) 0%,rgba(76,76,76,1) 50%);
  background: linear-gradient(135deg,  rgba(86,86,86,1) 0%,rgba(76,76,76,1) 50%);
  filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#565656', endColorstr='#4c4c4c',GradientType=1 );
  -webkit-box-shadow: 0px -1px 2px 0px rgba(0, 0, 0, 0.15);
  box-shadow: 0px -1px 2px 0px rgba(0, 0, 0, 0.15);
  -moz-transform:rotate(45deg);
  -webkit-transform:rotate(45deg);
  -o-transform:rotate(45deg);
  -ms-transform:rotate(45deg);
  transform:rotate(45deg);
}
.bar span {
  position:absolute;
  display:block;
  width:100%;
  height:64px;
  -webkit-border-radius:16px;
  border-radius:16px;
  top:0;
  left:0;
}
</style>

 <div class="progressbar" data-perc="50">
  <div class="bar color4"><span></span></div>
  <div class="label"><span></span></div>
</div>
<div style="clear:both;margin-bottom:50px;"></div>
