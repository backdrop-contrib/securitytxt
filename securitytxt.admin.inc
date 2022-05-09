<?php

/**
 * @file
 * Forms.
 *
 * This file provides the form related functions for the
 * 'admin/config/system/securitytxt{,/file,/sign}' paths.
 */

/**
 * Security.txt file configuration form.
 *
 * @ingroup forms
 */
function securitytxt_file_form() {
  $config = config('securitytxt.settings');

  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable the security.txt file for your site'),
    '#default_value' => $config->get('enabled'),
    '#description' => t('When enabled the security.txt file will be accessible to all users with the "view securitytxt" permission, you will almost certinaly want to give this permission to everyone i.e. authenticated and anonymous users.'),
  );

  $form['contact'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('You must provide at least one means of contact: email, phone or contact page URL.'),
  );
  $form['contact']['contact_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#default_value' => $config->get('contact_email'),
    '#description' => t('Typically this would be of the form <kbd>security@example.com</kbd>. Leave it blank if you do not want to provide an email address.'),
  );
  $form['contact']['contact_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone'),
    '#default_value' => $config->get('contact_phone'),
    '#description' => t('Use the full international format like <kbd>+1-201-555-0123</kbd> or <kbd>+44-1632-123456;ext=123</kbd>. Whitespace characters will be converted to dashes. Leave it blank if you do not want to provide a phone number.'),
  );
  $form['contact']['contact_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#default_value' => $config->get('contact_url'),
    '#description' => t('The URL of a contact page which should be loaded over HTTPS. Leave it blank if you do not want to provide a contact page.'),
  );

  $form['expires'] = array(
    '#type' => 'fieldset',
    '#title' => t('Expires'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('The date and time after which the content of the security.txt file should be considered stale. Make sure you update this value periodically and keep your file under review.'),
  );
  $form['expires']['expires_datetime'] = array(
    '#type' => 'html_datetime',
    '#title' => t('Expires'),
    '#default_value' => array(
      'date' => format_date($config->get('expires_timestamp'), 'custom', DATE_FORMAT_DATE),
      'time' => format_date($config->get('expires_timestamp'), 'custom', DATE_FORMAT_TIME),
    ),
    '#attributes' => array(
      'date' => array(
        'min' => format_date(REQUEST_TIME, 'custom', DATE_FORMAT_DATE),
        'max' => format_date(REQUEST_TIME + 5 * SECURITYTXT_SECONDS_IN_366_DAYS, 'custom', DATE_FORMAT_DATE),
      ),
    ),
    '#required' => TRUE,
    '#description' => t('The date and time after which the content of the security.txt file should be considered stale.'),
  );

  $form['encryption'] = array(
    '#type' => 'fieldset',
    '#title' => t('Encryption'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Allow people to send you encrypted messages by providing your public key.'),
  );
  $form['encryption']['encryption_key_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Public key URL'),
    '#default_value' => $config->get('encryption_key_url'),
    '#description' => t('The URL of page which contains your public key. The page should be loaded over HTTPS.'),
  );

  $form['acknowledgement'] = array(
    '#type' => 'fieldset',
    '#title' => t('Acknowledgements'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('A security acknowldgements page should list the individuals or companies that have disclosed security vulnerabilities and worked with you to fix them.'),
  );
  $form['acknowledgement']['acknowledgement_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Acknowledgements page URL'),
    '#default_value' => $config->get('acknowledgement_url'),
    '#description' => t('The URL of your security acknowledgements page. Leave it blank if you do not have such a page.'),
  );

  $form['languages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Preferred languages'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Select the languages which your security team speaks, you may select more than one language.'),
  );
  $form['languages']['preferred_languages'] = array(
    '#type' => 'select',
    '#title' => t('Preferred languages'),
    '#multiple' => TRUE,
    '#options' => _securitytxt_preferred_languages_options(),
    '#default_value' => $config->get('preferred_languages'),
    '#description' => t('Select zero or more languages. You can hold down your <kbd>Ctrl</kbd> key while clicking to select more than one language.'),
  );

  $form['canonical'] = array(
    '#type' => 'fieldset',
    '#title' => t('Canonical'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('The URLs for accessing your security.txt file. It is important to include this if you are digitally signing the security.txt file, so that the location of the security.txt file can be digitally signed too.'),
  );
  $form['canonical']['canonical_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Canonical URL'),
    '#default_value' => $config->get('canonical_url'),
    '#description' => t('The default value should be correct. Only edit this if you know what you are doing.'),
  );

  $form['policy'] = array(
    '#type' => 'fieldset',
    '#title' => t('Policy'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('A security and/or disclosure policy can help security researchers understand what you are looking for and how to report security vulnerabilities.'),
  );
  $form['policy']['policy_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Security policy URL'),
    '#default_value' => $config->get('policy_url'),
    '#description' => t('The URL of a page which provides details of your security and/or disclosure policy. Leave it blank if you do not have such a page.'),
  );

  $form['hiring'] = array(
    '#type' => 'fieldset',
    '#title' => t('Hiring'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('A link to any security-related job openings in your organisation.'),
  );
  $form['hiring']['hiring_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Hiring URL'),
    '#default_value' => $config->get('hiring_url'),
    '#description' => t('The URL of a page which provides details of any security-related job openings in your organisation. Leave it blank if you do not have such a page.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Security.txt file form validation.
 *
 * @ingroup forms
 */
function securitytxt_file_form_validate($form, &$form_state) {
  $enabled = $form_state['values']['enabled'];
  $contact_email = $form_state['values']['contact_email'];
  $contact_phone = $form_state['values']['contact_phone'];
  $contact_url = $form_state['values']['contact_url'];
  $expires_timestamp = _securitytxt_expires_timestamp($form_state);
  $encryption_key_url = $form_state['values']['encryption_key_url'];
  $acknowledgement_url = $form_state['values']['acknowledgement_url'];
  $preferred_languages = $form_state['values']['preferred_languages'];
  $canonical_url = $form_state['values']['canonical_url'];
  $policy_url = $form_state['values']['policy_url'];
  $hiring_url = $form_state['values']['hiring_url'];

  if ($contact_email != '' && valid_email_address($contact_email) == FALSE) {
    form_set_error('contact_email', t('The contact email address in invalid.'));
  }

  if ($contact_phone != '' && _securitytxt_valid_phone($contact_phone) == FALSE) {
    form_set_error('contact_phone', t('The contact phone number is invalid.'));
  }

  if ($contact_url != '' && valid_url($contact_url, TRUE) == FALSE) {
    form_set_error('contact_url', t('The contact URL is invalid, please ensure that it is an absolute URL.'));
  }

  /* When enabled, check that at least one contact field is specified. */
  if ($enabled && $contact_email == '' && $contact_phone == '' && $contact_url == '') {
    form_set_error('contact', t('You must specify at least one method of contact.'));
  }

  if ($enabled && $expires_timestamp < REQUEST_TIME) {
    form_set_error('expires_datetime', t('Your expiry date must not be in the past.'));
  }

  if ($enabled && $expires_timestamp > REQUEST_TIME + 5 * SECURITYTXT_SECONDS_IN_366_DAYS) {
    form_set_error('expires_datetime', t('Your expiry date should not be more than 5 years into the future, 1 year is the recommended maximum.'));
  }

  if ($encryption_key_url != '' && valid_url($encryption_key_url, TRUE) == FALSE) {
    form_set_error('encryption_key_url', t('The encryption key URL is invalid, please ensure that it is an absolute URL.'));
  }

  if ($acknowledgement_url != '' && valid_url($acknowledgement_url, TRUE) == FALSE) {
    form_set_error('acknowledgement_url', t('The acknowledgement URL is invalid, please ensure that it is an absolute URL.'));
  }

  $lang_codes = array_keys(_securitytxt_preferred_languages_options());
  foreach ($preferred_languages as $preferred_lang_code) {
    if (!in_array($preferred_lang_code, $lang_codes)) {
      form_set_error('preferred_languages', t('Your preferred language choice is invalid.'));
    }
  }

  if ($canonical_url != '' && valid_url($canonical_url, TRUE) == FALSE) {
    form_set_error('canonical_url', t('The canonical URL is invalid, please ensure that it is an absolute URL.'));
  }

  if ($policy_url != '' && valid_url($policy_url, TRUE) == FALSE) {
    form_set_error('policy_url', t('The policy URL is invalid, please ensure that it is an absolute URL.'));
  }

  if ($hiring_url != '' && valid_url($hiring_url, TRUE) == FALSE) {
    form_set_error('hiring_url', t('The hiring URL is invalid, please ensure that it is an absolute URL.'));
  }
}

/**
 * Security.txt file form submit.
 *
 * @ingroup forms
 */
function securitytxt_file_form_submit($form, &$form_state) {
  $config = config('securitytxt.settings');
  $config->set('enabled', $form_state['values']['enabled']);
  $config->set('contact_email', $form_state['values']['contact_email']);
  $config->set('contact_phone', _securitytxt_canonicalize_phone($form_state['values']['contact_phone']));
  $expires_timestamp = _securitytxt_expires_timestamp($form_state);
  $config->set('expires_timestamp', $expires_timestamp);
  $config->set('contact_url', $form_state['values']['contact_url']);
  $config->set('encryption_key_url', $form_state['values']['encryption_key_url']);
  $config->set('acknowledgement_url', $form_state['values']['acknowledgement_url']);
  $config->set('preferred_languages', $form_state['values']['preferred_languages']);
  $config->set('canonical_url', $form_state['values']['canonical_url']);
  $config->set('policy_url', $form_state['values']['policy_url']);
  $config->set('hiring_url', $form_state['values']['hiring_url']);
  $config->save();

  /* Warn if expires in more than 366 days into the future */
  if ($expires_timestamp > REQUEST_TIME + SECURITYTXT_SECONDS_IN_366_DAYS) {
    backdrop_set_message(t('It is recommended that your expiry date be less than a year into the future.'), 'warning');
  }

  /* Warn if contact URL is not loaded over HTTPS */
  if ($form_state['values']['contact_url'] != '' && substr($form_state['values']['contact_url'], 0, 8) !== 'https://') {
    backdrop_set_message(t('Your contact URL should really be loaded over HTTPS.'), 'warning');
  }

  /* Warn if encryption URL is not loaded over HTTPS */
  if ($form_state['values']['encryption_key_url'] != '' && substr($form_state['values']['encryption_key_url'], 0, 8) !== 'https://') {
    backdrop_set_message(t('Your public key URL should really be loaded over HTTPS.'), 'warning');
  }

  /* Warn if canonical URL is not default value */
  if ($form_state['values']['canonical_url'] != _securitytxt_default_canonical_url()) {
    backdrop_set_message(t('Your canonical URL is not the default value. This is unusual, only continue with this if you know what you are doing.'), 'warning');
  }

  /* Message the user to proceed to the sign page if they have enabled security.txt */
  if ($form_state['values']['enabled']) {
    backdrop_set_message(
      t(
        'You should now <a href="@sign">sign your security.txt file</a>.',
        array('@sign' => url('admin/config/system/securitytxt/sign'))
      )
    );
  }
}

/**
 * Security.txt sign configuration form.
 *
 * @ingroup forms
 */
function securitytxt_sign_form() {
  $config = config('securitytxt.settings');

  if (!$config->get('enabled')) {
    $form['instructions'] = array(
      '#type' => 'markup',
      '#markup' => '<p>' .
      t(
        'You must <a href="@configure">configure and enable</a> your security.txt file before you can sign it.',
        array('@configure' => url('admin/config/system/securitytxt'))
      ) .
      '</p>',
    );

    return $form;
  }

  $form['instructions'] = array(
    '#type' => 'markup',
    '#markup' => t(
      '<ol><li><a href="@download" download="security.txt">Download</a> your security.txt file.</li><li><p>Sign your security.txt file with the encryption key you specified in your security.txt file. You can do this with GPG with a command like:</p><p><kbd>gpg -u KEYID --output security.txt.sig  --armor --detach-sig security.txt</kbd></p></li><li>Paste the contents of the <kbd>security.txt.sig</kbd> file into the text box below.</li></ol>',
      array('@download' => url('.well-known/security.txt'))
    ),
  );
  $form['signature_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Signature'),
    '#default_value' => $config->get('signature_text'),
    '#rows' => 20,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Security.txt sign form validation.
 *
 * @ingroup forms
 */
function securitytxt_sign_form_validate($form, &$form_state) {
  /* There is currently no validation on the signature_text */
}

/**
 * Security.txt sign form submit.
 *
 * @ingroup forms
 */
function securitytxt_sign_form_submit($form, &$form_state) {
  config_set('securitytxt.settings', 'signature_text', $form_state['values']['signature_text']);
}

/**
 * Options array for the preferred languages options.
 */
function _securitytxt_preferred_languages_options() {
  include_once BACKDROP_ROOT . '/core/includes/standard.inc';

  $standard_language_list = standard_language_list();
  $options = array();

  foreach ($standard_language_list as $key => $value) {
    $options[$key] = $value[0];
  }

  return $options;
}

/**
 * Return the expires value as a unix timestamp from the $form_state.
 */
function _securitytxt_expires_timestamp(&$form_state) {
  $date = $form_state['values']['expires_datetime']['date'];
  $time = $form_state['values']['expires_datetime']['time'];
  $account = user_load($GLOBALS['user']->uid);
  $object = new BackdropDateTime($date . ' ' . $time, $account->timezone);

  return $object->getTimestamp();
}

/**
 * Basic validator for telephone numbers.
 */
function _securitytxt_valid_phone($phone) {
  $pattern = '/^\+\d{1,3}[\s\-\d]{5,30}(;ext=[\d]{1,8})?$/';

  if (preg_match($pattern, $phone)) {
    return TRUE;
  }

  return FALSE;
}

/**
 * Canonicalize a phone number.
 *
 * Replaces one or more whitespace characters with a hyphen.
 */
function _securitytxt_canonicalize_phone($phone) {
  $whitespace_replaced = preg_replace('/\s+/', '-', $phone);
  $hypens_deduplicated = preg_replace('/\-+/', '-', $whitespace_replaced);
  return $hypens_deduplicated;
}
