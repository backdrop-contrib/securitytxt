<?php

namespace Drupal\securitytxt\Form;

use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Url;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Path\AliasManagerInterface;
use Drupal\Core\Path\PathValidatorInterface;
use Drupal\Core\Routing\RequestContext;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Configure site information settings for this site.
 *
 *
 */
class SecuritytxtSignForm extends ConfigFormBase {

    /**
     * The path alias manager.
     *
     * @var \Drupal\Core\Path\AliasManagerInterface
     */
    protected $aliasManager;

    /**
     * The path validator.
     *
     * @var \Drupal\Core\Path\PathValidatorInterface
     */
    protected $pathValidator;

    /**
     * The request context.
     *
     * @var \Drupal\Core\Routing\RequestContext
     */
    protected $requestContext;

    /**
     * Constructs a SecuritytxtForm object.
     *
     * @param \Drupal\Core\Config\ConfigFactoryInterface $config_factory
     *   The factory for configuration objects.
     * @param \Drupal\Core\Path\AliasManagerInterface $alias_manager
     *   The path alias manager.
     * @param \Drupal\Core\Path\PathValidatorInterface $path_validator
     *   The path validator.
     * @param \Drupal\Core\Routing\RequestContext $request_context
     *   The request context.
     */
    public function __construct(ConfigFactoryInterface $config_factory, AliasManagerInterface $alias_manager, PathValidatorInterface $path_validator, RequestContext $request_context) {
        parent::__construct($config_factory);

        $this->aliasManager = $alias_manager;
        $this->pathValidator = $path_validator;
        $this->requestContext = $request_context;
    }

    /**
     * {@inheritdoc}
     */
    public static function create(ContainerInterface $container) {
        return new static(
            $container->get('config.factory'),
            $container->get('path.alias_manager'),
            $container->get('path.validator'),
            $container->get('router.request_context')
        );
    }

    /**
     * {@inheritdoc}
     */
    public function getFormId() {
        return 'securitytxt_sign';
    }

    /**
     * {@inheritdoc}
     */
    protected function getEditableConfigNames() {
        return ['securitytxt.settings'];
    }

    /**
     * {@inheritdoc}
     */
    public function buildForm(array $form, FormStateInterface $form_state) {
        $settings_config = $this->config('securitytxt.settings');

        $enabled = $settings_config->get('enabled');

        if (!$enabled) {
            $form['instructions'] = [
                '#type' => 'markup',
                '#markup' => '<p>' . t('You must <a href=":configure">configure and enable</a> your security.txt file before you can sign it.', [':configure' => Url::fromRoute('securitytxt.configure')->toString()]) . '</p>',
            ];

            return $form;
        }

        $form['instructions'] = [
            '#type' => 'markup',
            '#markup' => '<ol>' .
            '<li>' . t('<a href=":download" download="security.txt">Download</a> your security.txt file.', [':download' => Url::fromRoute('securitytxt.securitytxt_file')->toString()]) . '</li>' .
            '<li><p>Sign your security.txt file with the encryption key you specified in your security.txt file. You can do this with GPG with a command like:</p><p><kbd>gpg -u KEYID --output security.txt.sig  --armor --detach-sig security.txt</kbd></p></li>' .
            '<li>Paste the contents of the <kbd>security.txt.sig</kbd> file into the text box below.</li>' .
            '</ol>',
        ];
        $form['signature_text'] = [
            '#type' => 'textarea',
            '#title' => t('Signature'),
            '#default_value' => $settings_config->get('signature_text'),
            '#rows' => 20,
        ];

        return parent::buildForm($form, $form_state);
    }

    public function validateForm(array &$form, FormStateInterface $form_state) {
        /*
          $desire = $form_state->getValue('desire');

          if (strlen($desire) < 5) {
          $form_state->setErrorByName('desire', $this->t('Your desire must be at least 5 characters long.'));
          }
        */
    }

    public function submitForm(array &$form, FormStateInterface $form_state) {
        $this->config('securitytxt.settings')
            ->set('signature_text', $form_state->getValue('signature_text'))
            ->save();

        parent::submitForm($form, $form_state);
    }
}
