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
  $settings = variable_get('securitytxt', array());

  if ($settings['enabled']) {
    $content = '';

    $contact_email = $settings['contact_email'];
    if ($contact_email) {
      $content .= 'Contact: ' . $contact_email . "\n";
    }

    $contact_phone = $settings['contact_phone'];
    if ($contact_phone) {
      $content .= 'Contact: ' . $contact_phone . "\n";
    }

    $contact_url = $settings['contact_url'];
    if ($contact_url) {
      $content .= 'Contact: ' . $contact_url . "\n";
    }

    $encryption_key_url = $settings['encryption_key_url'];
    if ($encryption_key_url) {
      $content .= 'Encryption: ' . $encryption_key_url . "\n";
    }

    $policy_url = $settings['policy_url'];
    if ($policy_url) {
      $content .= 'Policy: ' . $policy_url . "\n";
    }

    $acknowledgement_url = $settings['acknowledgement_url'];
    if ($acknowledgement_url) {
      $content .= 'Acknowledgement: ' . $acknowledgement_url . "\n";
    }

    $signature_url = url('.well-known/security.txt.sig', array('absolute' => TRUE));
    $content .= 'Signature: ' . $signature_url . "\n";

    drupal_add_http_header('Content-Type', 'text/plain');
    print($content);
    drupal_exit();
  }
  else {
    drupal_not_found();
  }
}

/**
 * Security.txt signature page.
 */
function securitytxt_signature_page() {
  $settings = variable_get('securitytxt', array());

  if ($settings['enabled'] && $settings['signature_text']) {
    drupal_add_http_header('Content-Type', 'text/plain');
    print($settings['signature_text']);
    drupal_exit();
  }
  else {
    drupal_not_found();
  }
}
