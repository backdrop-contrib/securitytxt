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
  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable the security.txt file for your site'),
    '#default_value' => config_get('securitytxt.settings', 'enabled'),
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
    '#default_value' => config_get('securitytxt.settings', 'contact_email'),
    '#description' => t('Typically this would be of the form <kbd>security@example.com</kbd>. Leave it blank if you do not want to provide an email address.'),
  );
  $form['contact']['contact_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone'),
    '#default_value' => config_get('securitytxt.settings', 'contact_phone'),
    '#description' => t('Use the full international format like <kbd>+1-201-555-0123</kbd>. Leave it blank if you do not want to provide a phone number.'),
  );
  $form['contact']['contact_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#default_value' => config_get('securitytxt.settings', 'contact_url'),
    '#description' => t('The URL of a contact page which should be loaded over HTTPS. Leave it blank if you do not want to provide a contact page.'),
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
    '#default_value' => config_get('securitytxt.settings', 'encryption_key_url'),
    '#description' => t('The URL of page which contains your public key. The page should be loaded over HTTPS.'),
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
    '#default_value' => config_get('securitytxt.settings', 'policy_url'),
    '#description' => t('The URL of a page which provides details of your security and/or disclosure policy. Leave it blank if you do not have such a page.'),
  );

  $form['acknowledgement'] = array(
    '#type' => 'fieldset',
    '#title' => t('Acknowledgement'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('A security acknowldgements page should list the individuals or companies that have disclosed security vulnerabilities and worked with you to fix them.'),
  );
  $form['acknowledgement']['acknowledgement_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Acknowledgements page URL'),
    '#default_value' => config_get('securitytxt.settings', 'acknowledgement_url'),
    '#description' => t('The URL of your security acknowledgements page. Leave it blank if you do not have such a page.'),
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
  $encryption_key_url = $form_state['values']['encryption_key_url'];
  $policy_url = $form_state['values']['policy_url'];
  $acknowledgement_url = $form_state['values']['acknowledgement_url'];

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

  if ($encryption_key_url != '' && valid_url($encryption_key_url, TRUE) == FALSE) {
    form_set_error('encryption_key_url', t('The encryption key URL is invalid, please ensure that it is an absolute URL.'));
  }

  if ($policy_url != '' && valid_url($policy_url, TRUE) == FALSE) {
    form_set_error('policy_url', t('The policy URL is invalid, please ensure that it is an absolute URL.'));
  }

  if ($acknowledgement_url != '' && valid_url($acknowledgement_url, TRUE) == FALSE) {
    form_set_error('acknowledgement_url', t('The acknowledgement URL is invalid, please ensure that it is an absolute URL.'));
  }
}

/**
 * Security.txt file form submit.
 *
 * @ingroup forms
 */
function securitytxt_file_form_submit($form, &$form_state) {
  config_set('securitytxt.settings', 'enabled', $form_state['values']['enabled']);
  config_set('securitytxt.settings', 'contact_email', $form_state['values']['contact_email']);
  config_set('securitytxt.settings', 'contact_phone', $form_state['values']['contact_phone']);
  config_set('securitytxt.settings', 'contact_url', $form_state['values']['contact_url']);
  config_set('securitytxt.settings', 'encryption_key_url', $form_state['values']['encryption_key_url']);
  config_set('securitytxt.settings', 'policy_url', $form_state['values']['policy_url']);
  config_set('securitytxt.settings', 'acknowledgement_url', $form_state['values']['acknowledgement_url']);

  /* Warn if contact URL is not loaded over HTTPS */
  if ($form_state['values']['contact_url'] != '' && substr($form_state['values']['contact_url'], 0, 8) !== 'https://') {
    backdrop_set_message(t('Your contact URL should really be loaded over HTTPS.'), 'warning');
  }

  /* Warn if encryption URL is not loaded over HTTPS */
  if ($form_state['values']['encryption_key_url'] != '' && substr($form_state['values']['encryption_key_url'], 0, 8) !== 'https://') {
    backdrop_set_message(t('Your public key URL should really be loaded over HTTPS.'), 'warning');
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
  if (!config_get('securitytxt.settings', 'enabled')) {
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
      array('@download' => url('.well-known/security.txt')
    ),
  );
  $form['signature_text'] = array(
    '#type' => 'textarea',
    '#title' => t('Signature'),
    '#default_value' => config_get('securitytxt.settings', 'signature_text'),
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
 * Basic validator for telephone numbers.
 */
function _securitytxt_valid_phone($phone) {
  $pattern = '/^[ext,\d\s\-\+]{5,30}$/';

  if (preg_match($pattern, $phone)) {
    return TRUE;
  }

  return FALSE;
}
