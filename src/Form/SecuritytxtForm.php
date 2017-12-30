<?php

namespace Drupal\securitytxt\Form;

use Drupal\Core\Form\FormBase;
use Drupal\Core\Form\FormStateInterface;

class SecuritytxtForm extends FormBase {

    /* See https://tools.ietf.org/html/draft-foudil-securitytxt-02 */
    public function buildForm(array $form, FormStateInterface $form_state) {
        $form['enabled'] = [
            '#type' => 'checkbox',
            '#title' => t('Enabled'),
            '#default_value' => 0,
            '#description' => t('Enable the security.txt file for your site.'),
        ];

        $form['contacts'] = [
            '#type' => 'details',
            '#title' => t('Contacts'),
            '#open' => TRUE,
        ];
        $form['contacts']['email'] = [
            '#type' => 'email',
            '#title' => t('Contact Email'),
            '#default_value' => '',
            '#description' => t('The most common contact option is an email address, but we need to allow multiples, as well as phone numbers and URLs in the future.'),
            '#required' => TRUE,
        ];

        $form['encryption'] = [
            '#type' => 'details',
            '#title' => t('Encryption'),
            '#open' => TRUE,
        ];
        $form['encryption']['url'] = [
            '#type' => 'url',
            '#title' => t('URL of encryption key'),
            '#size' => 30,
        ];

        $form['acknowledgements'] = [
            '#type' => 'details',
            '#title' => t('Acknowledgements'),
            '#open' => TRUE,
        ];
        $form['acknowledgements']['url'] = [
            '#type' => 'url',
            '#title' => t('URL of acknowledgements'),
            '#size' => 30,
        ];

        $form['policy'] = [
            '#type' => 'details',
            '#title' => t('Policy'),
            '#open' => TRUE,
        ];
        $form['policy']['url'] = [
            '#type' => 'url',
            '#title' => t('URL of security policy'),
            '#size' => 30,
        ];

        $form['signature'] = [
            '#type' => 'details',
            '#title' => t('Signature'),
            '#open' => TRUE,
        ];
        $form['signature']['url'] = [
            '#type' => 'url',
            '#title' => t('URL to signature of this security.txt file'),
            '#size' => 30,
        ];

        return $form;
    }

  public function getFormId() {
    return 'securitytxt_form';
  }

  public function validateForm(array &$form, FormStateInterface $form_state) {
    $desire = $form_state->getValue('desire');

    if (strlen($desire) < 5) {
      $form_state->setErrorByName('desire', $this->t('Your desire must be at least 5 characters long.'));
    }
  }

  public function submitForm(array &$form, FormStateInterface $form_state) {
    $desire = $form_state->getValue('desire');

    drupal_set_message(t('Your desire was: %desire.', ['%desire' => $desire]));
  }
}
