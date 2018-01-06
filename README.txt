		      ━━━━━━━━━━━━━━━━━━━━━━━━━━━━
		       SECURITY.TXT MODULE README


			    Daniel J. R. May
		      ━━━━━━━━━━━━━━━━━━━━━━━━━━━━


Table of Contents
─────────────────

1 Introduction
2 Installation
3 Configuration
.. 3.1 Permissions
.. 3.2 Security.txt configuration
.. 3.3 Security.txt signing
4 Use
5 Further reading





1 Introduction
══════════════

  The Security.txt module provides an implementation of the security.txt
  draft RFC standard. It’s purpose is to provide a standardised way to
  document your website’s security contact details and policy. This
  allows users and security researchers to securely disclose security
  vulnerabilities to you.


2 Installation
══════════════

  This module should be installed in the usual way. [Read about
  installing Drupal 8 modules].


  [Read about installing Drupal 8 modules]
  https://www.drupal.org/docs/8/extending-drupal-8/installing-drupal-8-modules


3 Configuration
═══════════════

  Once you have installed this module you will want to perform the
  following configuration.


3.1 Permissions
───────────────

  You control the permissions each role gets at
  `/admin/people/permissions'. You will almost certainly want to give
  everybody the `View security.txt' permission, i.e. give it to both the
  `Anoymous User' and `Authenticated User' roles.

  You will only want to give the `Administer security.txt' permission to
  very trusted roles.


3.2 Security.txt configuration
──────────────────────────────

  The Security.txt configuration page is under `System' on the Drupal
  configuration page. Once you have filled in all the details you want
  to add to your `security.txt' file and pressed the `Save
  configuration' button you will want to proceed to the `Sign' tab of
  the configuration form.


3.3 Security.txt signing
────────────────────────

  Once you have enabled your `security.txt' file you will want to
  provide a digital signature for it by following the instructions on
  the `Sign' tab of the configuration page.


4 Use
═════

  Once you have completed the configuration of the Security.txt module
  your security.txt and security.txt.sig files which be available at the
  following standard URLs:

  • /.well-known/security.txt
  • /.well-known/security.txt.sig


5 Further reading
═════════════════

  • Learn more about the [security.txt standard]
  • Read the [draft RFC]


  [security.txt standard] https://securitytxt.org/

  [draft RFC] https://tools.ietf.org/html/draft-foudil-securitytxt-02
