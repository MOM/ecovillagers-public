<?php

/**
 * @file
 * MailSystemInterface class definition
 */

class EmailWrappersMailSystemInterface implements MailSystemInterface {

  public function format(array $message) {
    $message['body'] = implode("\n\n", $message['body']);
    return $message;
  }

  public function mail(array $message) {
    // tweak headers

    $message['headers']['Content-Type'] = 'multipart/alternative; charset=UTF-8; boundary="' . $message['params']['boundary'] . '"';
    $mimeheaders = array();

    foreach ($message['headers'] as $name => $value) {

      $mimeheaders[] = $name . ':' . mime_header_encode($value);
    }
    $line_endings = variable_get('mail_line_endings', MAIL_LINE_ENDINGS);
    return mail(
      $message['to'],
      mime_header_encode($message['subject']),

      preg_replace('@\r?\n@', $line_endings, $message['body']),

      join("\n", $mimeheaders)
    );
  }

}
