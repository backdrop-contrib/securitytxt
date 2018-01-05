<?php

namespace Drupal\securitytxt;

use Drupal\Core\Url;

/**
 * Securitytxt service class.
 */
class SecuritytxtService {

    public function isEnabled() {
        if (TRUE) {
            return TRUE;
        } else {
            return FALSE;
        }
    }

    public function getSecuritytxtFile() {
        $settings_config = \Drupal::config('securitytxt.settings');

        $enabled = $settings_config->get('enabled');
        $contact_email = $settings_config->get('contact_email');
        $contact_phone = $settings_config->get('contact_phone');
        $contact_url = $settings_config->get('contact_url');
        $encryption_key_url = $settings_config->get('encryption_key_url');
        $policy_url = $settings_config->get('policy_url');
        $acknowledgement_url = $settings_config->get('acknowledgement_url');
        $signature_url = Url::fromRoute('securitytxt.securitytxt_signature')->setAbsolute()->toString();

        if ($enabled) {
            $content = '';

            if ($contact_email != '') {
                $content .= 'Contact: ' . $contact_email . "\n";
            }

            if ($contact_phone) {
                $content .= 'Contact: ' . $contact_phone . "\n";
            }

            if ($contact_url != '') {
                $content .= 'Contact: ' . $contact_url . "\n";
            }

            if ($encryption_key_url != '') {
                $content .= 'Encryption: ' . $encryption_key_url . "\n";
            }

            if ($policy_url != '') {
                $content .= 'Policy: ' . $policy_url . "\n";
            }

            if ($acknowledgement_url != '') {
                $content .= 'Acknowledgement: ' . $acknowledgement_url . "\n";
            }

            $content .= 'Signature: ' . $signature_url . "\n";

            return $content;
        } else {
            throw new \Symfony\Component\HttpKernel\Exception\NotFoundHttpException();
        }
    }

    public function getSecuritytxtSignature() {
        $settings_config = \Drupal::config('securitytxt.settings');

        $enabled = $settings_config->get('enabled');
        $signature_text = $settings_config->get('signature_text');

        if ($enabled) {
            return $signature_text;
        } else {
            throw new \Symfony\Component\HttpKernel\Exception\NotFoundHttpException();
        }
    }
}