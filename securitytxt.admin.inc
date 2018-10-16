<?php

/**
 * Security.txt file configuration form.
 *
 * @ingroup forms
 */
function securitytxt_file_form() {
  $form['description'] = array(
    '#markup' => '<p>' . t("This is the security.txt file configuration form.") . '</p>',
  );


  return $form;
}

/**
 * Security.txt sign configuration form.
 *
 * @ingroup forms
 */
function securitytxt_sign_form() {
  $form['description'] = array(
    '#markup' => '<p>' . t("This is the security.txt SIGN configuration form.") . '</p>',
  );

  return $form;
}


/*
SCHEMA

securitytxt.settings:
  type: config_object
  label: 'Security.txt settings'
  mapping:
    enabled:
      type: boolean
      label: 'Enable security.txt'
    contact_email:
      type: email
      label: 'Contact email'
    contact_phone:
      type: string
      label: 'Contact phone'
    contact_page_url:
      type: string
      label: 'Contact page URL'
    encryption_public_key_url:
      type: string
      label: 'Public key URL'
    policy_page_url:
      type: string
      label: 'Security policy page URL'
    acknowledgement_page_url:
      type: string
      label: 'Acknowldegment page URL'
    signature_text:
      type: string
      label: 'Plain text PGP signature of security.txt'
 */