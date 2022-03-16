<?php

/**
 * @file
 * Page callbacks.
 *
 * This file provides the page callback functions for the
 * .well-known/security.txt and .well-known/security.txt.sig paths.
 */

/**
 * Security.txt file page.
 */
function securitytxt_file_page() {
  if (!config_get('securitytxt.settings', 'enabled')) {
    backdrop_not_found();
    backdrop_exit();
  }

  $content = '';

  $contact_email = config_get('securitytxt.settings', 'contact_email');
  if ($contact_email) {
    $content .= 'Contact: ' . $contact_email . "\n";
  }

  $contact_phone = config_get('securitytxt.settings', 'contact_phone');
  if ($contact_phone) {
    $content .= 'Contact: ' . $contact_phone . "\n";
  }

  $contact_url = config_get('securitytxt.settings', 'contact_url');
  if ($contact_url) {
    $content .= 'Contact: ' . $contact_url . "\n";
  }

  $encryption_key_url = config_get('securitytxt.settings', 'encryption_key_url');
  if ($encryption_key_url) {
    $content .= 'Encryption: ' . $encryption_key_url . "\n";
  }

  $policy_url = config_get('securitytxt.settings', 'policy_url');
  if ($policy_url) {
    $content .= 'Policy: ' . $policy_url . "\n";
  }

  $acknowledgement_url = config_get('securitytxt.settings', 'acknowledgement_url');
  if ($acknowledgement_url) {
    $content .= 'Acknowledgement: ' . $acknowledgement_url . "\n";
  }

  $signature_url = url('.well-known/security.txt.sig', array('absolute' => TRUE));
  $content .= 'Signature: ' . $signature_url . "\n";

  backdrop_add_http_header('Content-Type', 'text/plain');
  print($content);
  backdrop_exit();
}

/**
 * Security.txt signature page.
 */
function securitytxt_signature_page() {
  $enabled = config_get('securitytxt.settings', 'enabled');
  $signature_text = config_get('securitytxt.settings', 'signature_text');

  if ($enabled && $signature_text) {
    backdrop_add_http_header('Content-Type', 'text/plain');
    print($signature_text);
  } else {
    backdrop_not_found();
  }

  backdrop_exit();
}
