TROUBLESHOOTING
---------------

Problem:  Test fails with the message, "Page wrapper preview displays expected
          template content"
Solution: The problem stems from the test files directory is unwritable.  The
          test directory will not necessarily inherit the owner:group as the
          parent directory.  The solution is to make sure the web server will
          always have write access to anything created in the files directory.
          One method is to change the web user used.  In httpd.conf, search for
          "^User" and replace the value with a user that owns the files
          directory.  After modifying httpd.conf, restart the web server.
