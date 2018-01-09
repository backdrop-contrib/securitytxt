<?php

namespace Drupal\Tests\securitytxt\Functional;

/**
 * Permission check.
 *
 * Verify that the securitytxt module permissions grant/deny access to
 * the pages we expect.
 *
 * @group securitytxt
 */
class SecuritytxtPermissionsTest extends SecuritytxtBaseTest {

  /**
   * Test permissions to all Security.txt paths when Security.txt is disabled.
   */
  public function testDisabledAccess() {
    /* Test access for Anonymous role with no permissions. */
    $this->drupalGet('admin/config/system/securitytxt');
    $this->assertResponse(403, 'Access denied for Anonymous user to securitytxt configure page.');
    $this->drupalGet('admin/config/system/securitytxt/sign');
    $this->assertResponse(403, 'Access denied for Anonymous user to securitytxt sign page.');
    $this->drupalGet('.well-known/security.txt');
    $this->assertResponse(403, 'Access denied for Anonymous user to security.txt page.');
    $this->drupalGet('.well-known/security.txt.sig');
    $this->assertResponse(403, 'Access denied for Anonymous user to security.txt.sig page.');

    /* Test access for Authenticated user with no permissions. */
    $this->drupalLogin($this->authenticatedUser);
    $this->drupalGet('admin/config/system/securitytxt');
    $this->assertResponse(403, 'Access denied for Authenticated user with no permissions to securitytxt configure page.');
    $this->drupalGet('admin/config/system/securitytxt/sign');
    $this->assertResponse(403, 'Access denied for Authenticated user with no permissions to securitytxt sign page.');
    $this->drupalGet('.well-known/security.txt');
    $this->assertResponse(403, 'Access denied for Authenticated user with no permissions to security.txt page.');
    $this->drupalGet('.well-known/security.txt.sig');
    $this->assertResponse(403, 'Access denied for Authenticated user with no permissions to security.txt.sig page.');
    $this->drupalLogout();

    /* Test access for Authenticated user with 'view securitytxt' permissions. */
    $this->drupalLogin($this->viewPermissionUser);
    $this->drupalGet('admin/config/system/securitytxt');
    $this->assertResponse(403, 'Access denied for Authenticated user with "view securitytxt" to securitytxt configure page.');
    $this->drupalGet('admin/config/system/securitytxt/sign');
    $this->assertResponse(403, 'Access denied for Authenticated user with "view securitytxt" to securitytxt sign page.');
    $this->drupalGet('.well-known/security.txt');
    $this->assertResponse(404, 'File Not Found for Authenticated user with "view securitytxt" to security.txt page.');
    $this->drupalGet('.well-known/security.txt.sig');
    $this->assertResponse(404, 'File Not Found for Authenticated user with "view securitytxt" to security.txt.sig page.');
    $this->drupalLogout();

    /* Test access for Authenticated user with 'administer securitytxt' permissions. */
    $this->drupalLogin($this->administerPermissionUser);
    $this->drupalGet('admin/config/system/securitytxt');
    $this->assertResponse(200, 'Access granted to Authenticated user with "administer securitytxt" to securitytxt configure page.');
    $this->drupalGet('admin/config/system/securitytxt/sign');
    $this->assertResponse(200, 'Access granted to Authenticated user with "administer securitytxt" to securitytxt sign page.');
    $this->drupalGet('.well-known/security.txt');
    $this->assertResponse(403, 'Access denied for Authenticated user with "administer securitytxt" to security.txt page.');
    $this->drupalGet('.well-known/security.txt.sig');
    $this->assertResponse(403, 'Access denied for Authenticated user with "administer securitytxt" to security.txt.sig page.');
    $this->drupalLogout();

    /* Test access for Authenticated user with 'view securitytxt' & 'administer securitytxt' permissions. */
    $this->drupalLogin($this->viewAndAdministerPermissionUser);
    $this->drupalGet('admin/config/system/securitytxt');
    $this->assertResponse(200, 'Access granted to Authenticated user with both securitytxt perms to securitytxt configure page.');
    $this->drupalGet('admin/config/system/securitytxt/sign');
    $this->assertResponse(200, 'Access granted to Authenticated user with both securitytxt perms to securitytxt sign page.');
    $this->drupalGet('.well-known/security.txt');
    $this->assertResponse(404, 'Access denied for Authenticated user with both securitytxt perms to security.txt page.');
    $this->drupalGet('.well-known/security.txt.sig');
    $this->assertResponse(404, 'Access denied for Authenticated user with both securitytxt perms to security.txt.sig page.');
    $this->drupalLogout();
  }

  /**
   * Test permissions to all Security.txt paths when Security.txt is enabled.
   */
  public function testEnabledAccess() {
    /* Define the configuration. */
    $enabled = TRUE;
    $contact_email = 'user.name@example.com';
    $contact_phone = '+44-7700-900123';
    $contact_url = 'https://example.com/contact';
    $encryption_key_url = 'https://example.com/key';
    $policy_url = 'https://example.com/policy';
    $acknowledgement_url = 'https://example.com/acknowledgement';
    $signature_text = $this->randomMachineName(512);

    /* Log in, enable, configure & sign the security.txt file. */
    $this->drupalLogin($this->administerPermissionUser);
    $this->submitConfigureForm($enabled, $contact_email, $contact_phone, $contact_url, $encryption_key_url, $policy_url, $acknowledgement_url);
    $this->submitSignForm($signature_text);
    $this->drupalLogout();

    /* Repeat the access permission tests. */
    /* Test access for Anonymous role with no permissions. */
    $this->drupalGet('admin/config/system/securitytxt');
    $this->assertResponse(403, 'Access denied for Anonymous user to securitytxt configure page.');
    $this->drupalGet('admin/config/system/securitytxt/sign');
    $this->assertResponse(403, 'Access denied for Anonymous user to securitytxt sign page.');
    $this->drupalGet('.well-known/security.txt');
    $this->assertResponse(403, 'Access denied for Anonymous user to security.txt page.');
    $this->drupalGet('.well-known/security.txt.sig');
    $this->assertResponse(403, 'Access denied for Anonymous user to security.txt.sig page.');

    /* Test access for Authenticated user with no permissions. */
    $this->drupalLogin($this->authenticatedUser);
    $this->drupalGet('admin/config/system/securitytxt');
    $this->assertResponse(403, 'Access denied for Authenticated user with no permissions to securitytxt configure page.');
    $this->drupalGet('admin/config/system/securitytxt/sign');
    $this->assertResponse(403, 'Access denied for Authenticated user with no permissions to securitytxt sign page.');
    $this->drupalGet('.well-known/security.txt');
    $this->assertResponse(403, 'Access denied for Authenticated user with no permissions to security.txt page.');
    $this->drupalGet('.well-known/security.txt.sig');
    $this->assertResponse(403, 'Access denied for Authenticated user with no permissions to security.txt.sig page.');
    $this->drupalLogout();

    /* Test access for Authenticated user with 'view securitytxt' permissions. */
    $this->drupalLogin($this->viewPermissionUser);
    $this->drupalGet('admin/config/system/securitytxt');
    $this->assertResponse(403, 'Access denied for Authenticated user with "view securitytxt" to securitytxt configure page.');
    $this->drupalGet('admin/config/system/securitytxt/sign');
    $this->assertResponse(403, 'Access denied for Authenticated user with "view securitytxt" to securitytxt sign page.');
    $this->drupalGet('.well-known/security.txt');
    $this->assertResponse(200, 'Accesss granted for Authenticated user with "view securitytxt" to security.txt page.');
    $this->drupalGet('.well-known/security.txt.sig');
    $this->assertResponse(200, 'Access granted for Authenticated user with "view securitytxt" to security.txt.sig page.');
    $this->drupalLogout();

    /* Test access for Authenticated user with 'administer securitytxt' permissions. */
    $this->drupalLogin($this->administerPermissionUser);
    $this->drupalGet('admin/config/system/securitytxt');
    $this->assertResponse(200, 'Access granted to Authenticated user with "administer securitytxt" to securitytxt configure page.');
    $this->drupalGet('admin/config/system/securitytxt/sign');
    $this->assertResponse(200, 'Access granted to Authenticated user with "administer securitytxt" to securitytxt sign page.');
    $this->drupalGet('.well-known/security.txt');
    $this->assertResponse(403, 'Access denied for Authenticated user with "administer securitytxt" to security.txt page.');
    $this->drupalGet('.well-known/security.txt.sig');
    $this->assertResponse(403, 'Access denied for Authenticated user with "administer securitytxt" to security.txt.sig page.');
    $this->drupalLogout();

    /* Test access for Authenticated user with 'view securitytxt' & 'administer securitytxt' permissions. */
    $this->drupalLogin($this->viewAndAdministerPermissionUser);
    $this->drupalGet('admin/config/system/securitytxt');
    $this->assertResponse(200, 'Access granted to Authenticated user with both securitytxt perms to securitytxt configure page.');
    $this->drupalGet('admin/config/system/securitytxt/sign');
    $this->assertResponse(200, 'Access granted to Authenticated user with both securitytxt perms to securitytxt sign page.');
    $this->drupalGet('.well-known/security.txt');
    $this->assertResponse(200, 'Access granted for Authenticated user with both securitytxt perms to security.txt page.');
    $this->drupalGet('.well-known/security.txt.sig');
    $this->assertResponse(200, 'Access granted for Authenticated user with both securitytxt perms to security.txt.sig page.');
    $this->drupalLogout();
  }

}
