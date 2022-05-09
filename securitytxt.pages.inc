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
  $config = config('securitytxt.settings');

  if (!$config->get('enabled')) {
    backdrop_not_found();
    backdrop_exit();
  }

  $content = '';

  $contact_email = $config->get('contact_email');
  if ($contact_email) {
    $content .= 'Contact: mailto:' . $contact_email . "\n";
  }

  $contact_phone = $config->get('contact_phone');
  if ($contact_phone) {
    $content .= 'Contact: tel:' . $contact_phone . "\n";
  }

  $contact_url = $config->get('contact_url');
  if ($contact_url) {
    $content .= 'Contact: ' . $contact_url . "\n";
  }

  $expires_timestamp = $config->get('expires_timestamp');
  if ($expires_timestamp) {
    $content .= 'Expires: ' . date('c', $expires_timestamp) . "\n";
  }

  $encryption_key_url = $config->get('encryption_key_url');
  if ($encryption_key_url) {
    $content .= 'Encryption: ' . $encryption_key_url . "\n";
  }

  $policy_url = $config->get('policy_url');
  if ($policy_url) {
    $content .= 'Policy: ' . $policy_url . "\n";
  }

  $acknowledgement_url = $config->get('acknowledgement_url');
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
  $config = config('securitytxt.settings');

  $enabled = $config->get('enabled');
  $signature_text = $config->get('signature_text');

  if ($enabled && $signature_text) {
    backdrop_add_http_header('Content-Type', 'text/plain');
    print($signature_text);
  }
  else {
    backdrop_not_found();
  }

  backdrop_exit();
}
