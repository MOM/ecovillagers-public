<?php
/**
 * @file
 * List of tokens available for the confirmation token selector WYSIWYG tool.
 *
 * Available variables:
 * - $tokens: All available confirmation page tokens.
 */
?>

<style type="text/css">
  #fundraiser-confirmation-tokens {
    background-color: #FFF;
    margin: 20px;
    padding: 10px;
  }

  #fundraiser-confirmation-tokens select {
    width: 350px;
  }

  #fundraiser-confirmation-tokens h2 {
    margin-top: 10px;
  }

  #fundraiser-confirmation-tokens em {
    font-size: .8em;
  }
</style>

<script type="text/javascript">

 function responseVal(e) {
   window.returnValue = e.value;
   window.close();
 }

</script>

<div id="fundraiser-confirmation-tokens">
  <h1>Insert tokens</h1>
  <p>Select the token you wish to insert into the confirmation message.</p>
  <?php foreach ($tokens as $token_type => $token_list) : ?>
    <h2><?php print ucfirst($token_type); ?> Tokens</h2>
    <select id="<?php print $token_type . '-tokens'; ?>" onchange="responseVal(this)">
      <option value="">-- Select --</option>
      <?php foreach ($token_list as $k => $v) : ?>
        <option value="<?php print $k;?>"><?php print $v;?></option>
      <?php endforeach; ?>
    </select>
  <?php endforeach; ?>

  <p><em>After you make your selection this dialog window will close and the token will be inserted at the cursor's current position.</em></p>
</div>
