Security.txt
============

The `securitytxt` module provides the [security.txt
standard](https://securitytxt.org/) for Backdrop CMS.

Its purpose is to provide a standardised way to document your
website’s security contact details and policy. This allows people to
securely disclose vulnerabilities to you.

Requirements
------------

You must replace your `.htaccess` file with the one provided by this
module at `htaccess/modified.htaccess`. This will be required until a
fix for "[issue
5583](https://github.com/backdrop/backdrop-issues/issues/5583#issue-1200228154)"
has made its way into your version of backdrop.

**Note:** `htaccess/original.htaccess` is a copy of the default
`.htaccess` file from backdrop version 1.21.4 which
`modified.htaccess` is based on, it is only present for comparison
purposes.

Installation
------------

- Install this module in the usual way, see the [contributed
  modules](https://docs.backdropcms.org/documentation/contributed-modules)
  of the user guide for details.

- Replace your `.htaccess` file with the one provided by this module
  at `htaccess/modified.htaccess`, e.g. `cp
  PATH_TO_CONTRIB_MODULES/securitytxt/htaccess/modified.htaccess
  PATH_TO_DOCUMENT_ROOT/.htacess`.
  
- Visit the configuration page under Administration > Configuration > System >
  Security.txt (`admin/config/system/securitytxt`) and enter the
  required information to create your security.txt file.

- Once you have created your security.txt file you should provide a
  signature for it by visiting Administration > Configuration > System >
  Sign (`admin/config/system/securitytxt/sign`) and following the
  instructions.
  
- Once you have completed all this configuration your security.txt
  and security.txt.sig files will be available at the following standard URLs:
  - `/.well-known/security.txt`
  - `/.well-known/security.txt.sig`

<!-- Do not include if you have not created a wiki page. 
Documentation 
-------------

Additional documentation is located in [the -->
<!-- Wiki](https://github.com/backdrop-contrib/foo-project/wiki/Documentation).

# Further reading

-   Learn more about the [security.txt standard](https://securitytxt.org/)
-   Read the [draft RFC](https://tools.ietf.org/html/draft-foudil-securitytxt-02)

-->

Issues
------

Bugs and feature requests should be reported in [the Issue
Queue](https://github.com/backdrop-contrib/securitytxt/issues).

Current Maintainers
-------------------

- [Daniel J. R. May](https://github.com/danieljrmay).

Credits
-------

- Ported to Backdrop CMS by [Daniel J. R. May](https://github.com/danieljrmay).
- Originally written for Drupal by [Daniel J. R. May](https://github.com/danieljrmay).

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this
directory for complete text.
