<?php

namespace Drupal\Tests\securitytxt\Functional;

use Drupal\Tests\BrowserTestBase;

/**
 * Defines a base class for testing the Security.txt module.
 *
 * @group securitytxt
 */
abstract class SecuritytxtBaseTest extends BrowserTestBase {

  /**
   * Modules to enable.
   *
   * @var array
   *  Modules which should be enabled by default.
   */
  public static $modules = ['securitytxt'];

  /**
   * User with no permissions.
   *
   * @var \Drupal\user\Entity\User
   */
  protected $authenticatedUser;

  /**
   * User with the 'view securitytxt' permission.
   *
   * @var \Drupal\user\Entity\User
   */
  protected $viewPermissionUser;

  /**
   * User with the 'administer securitytxt' permission.
   *
   * @var \Drupal\user\Entity\User
   */
  protected $administerPermissionUser;

  /**
   * User with the 'view securitytxt' and 'administer securitytxt' permissions.
   *
   * @var \Drupal\user\Entity\User
   */
  protected $viewAndAdministerPermissionUser;

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();

    $this->authenticatedUser = $this->drupalCreateUser([]);
    $this->viewPermissionUser = $this->drupalCreateUser(['view securitytxt']);
    $this->administerPermissionUser = $this->drupalCreateUser(['administer securitytxt']);
    $this->viewAndAdministerPermissionUser = $this->drupalCreateUser(['view securitytxt', 'administer securitytxt']);
  }

  /**
   * Submit the Security.txt  module’s form.
   *
   * @param bool $enabled
   *   The value for the enabled checkbox.
   * @param string $contact_email
   *   The value for the contact 'Email' textfield.
   * @param string $contact_phone
   *   The value for the contact 'Phone' textfield.
   * @param string $contact_url
   *   The value for the contact 'URL' textfield.
   * @param string $encryption_key_url
   *   The value for the 'Public key URL' textfield.
   * @param string $policy_url
   *   The value for the 'Security policy URL' textfield.
   * @param string $acknowledgement_url
   *   The value for the 'Acknowledgements page URL' textfield.
   */
  protected function submitConfigureForm($enabled, $contact_email, $contact_phone, $contact_url, $encryption_key_url, $policy_url, $acknowledgement_url) {
    $path = 'admin/config/system/securitytxt';
    $edit = [
      'enabled' => $enabled,
      'contact_email' => $contact_email,
      'contact_phone' => $contact_phone,
      'contact_url' => $contact_url,
      'encryption_key_url' => $encryption_key_url,
      'policy_url' => $policy_url,
      'acknowledgement_url' => $acknowledgement_url,
    ];
    $submit = 'Save configuration';
    $options = [];
    $this->drupalPostForm($path, $edit, $submit, $options);
  }

  /**
   * Submit the Security.txt module’s 'Sign' form.
   *
   * @param string $signature_text
   *   The value for the 'Acknowledgements page URL' textfield.
   */
  protected function submitSignForm($signature_text) {
    $path = 'admin/config/system/securitytxt/sign';
    $edit = [
      'signature_text' => $signature_text,
    ];
    $submit = 'Save configuration';
    $options = [];
    $this->drupalPostForm($path, $edit, $submit, $options);
  }

}
